/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:28:53 by root              #+#    #+#             */
/*   Updated: 2024/11/17 18:50:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *handle_quotes(const char *input, int *i);

void free_command(t_command *cmd)
{
	size_t i;

	if (!cmd)
		return;
	i = 0;
	while (i < cmd->arg_count)
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_file)
		free(cmd->output_file);
	free_command(cmd->next);
	free(cmd);
}

char **tokenize_input(const char *input, size_t *token_count)
{
	char **tokens = malloc(128 * sizeof(char *));
	size_t count = 0, i = 0;
	size_t len = strlen(input);

	while (i < len)
	{
		// Skip whitespace
		while (isspace(input[i]))
			i++;

		if (input[i] == '\0')
			break;

		if (input[i] == '\'' || input[i] == '"')
		{
			// Handle quoted strings
			char *quoted = handle_quotes(input, (int *)&i);
			tokens[count++] = quoted;
		}
		else if (strchr("|<>", input[i]))
		{
			// Handle operators as single tokens
			char operator[3] = { input[i],
								 '\0',
								 '\0' };
			if (input[i] == '>' && input[i + 1] == '>') // Handle >>
			{
				operator[1] = '>';
				i++;
			}
			tokens[count++] = ft_strdup(operator);
			i++;
		}
		else
		{
			// Handle regular tokens
			size_t start = i;
			while (input[i] && !isspace(input[i]) && !strchr("|<>", input[i]) && input[i] != '\'' && input[i] != '"')
				i++;

			size_t length = i - start;
			tokens[count] = malloc(length + 1);
			ft_strncpy(tokens[count], input + start, length);
			tokens[count][length] = '\0';
			count++;
		}
	}
	tokens[count] = NULL; // Null-terminate the array
	*token_count = count;
	return tokens;
}

char *handle_quotes(const char *input, int *i)
{
	char quote = input[*i];
	char *result = malloc(1024); // Allocate a buffer
	int j = 0;

	(*i)++; // Skip the opening quote
	while (input[*i])
	{
		if (input[*i] == '\\' && (input[*i + 1] == '"' || input[*i + 1] == '\'' || input[*i + 1] == '\\'))
		{
			// Handle escaped characters within quotes
			result[j++] = input[++(*i)];
		}
		else if (input[*i] == quote)
		{
			// End of quoted string
			(*i)++;
			break;
		}
		else
		{
			result[j++] = input[*i];
		}
		(*i)++;
	}

	result[j] = '\0';
	return result;
}

char *expand_variables(const char *arg)
{
	if (arg[0] != '$')
		return ft_strdup(arg); // Not a variable, return as is

	char *var_name = ft_strdup(arg + 1);
	char *value = getenv(var_name); // Get environment variable value
	free(var_name);

	return value ? ft_strdup(value) : ft_strdup(""); // Return value or empty string
}

t_command *parse_input(const char *input)
{
	size_t token_count = 0;
	char **tokens = tokenize_input(input, &token_count);
	t_command *cmd = malloc(sizeof(t_command));

	cmd->args = malloc((token_count + 1) * sizeof(char *));
	cmd->arg_count = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append = 0;
	cmd->next = NULL;

	for (size_t i = 0; i < token_count; i++)
	{
		if (strcmp(tokens[i], "|") == 0)
		{
			// Handle pipe: isolate tokens after the pipe
			if (i + 1 < token_count)
			{
				char **remaining_tokens = &tokens[i + 1];
				size_t remaining_count = token_count - (i + 1);

				// Convert remaining tokens into a single string for parsing
				size_t remaining_length = 0;
				for (size_t j = 0; j < remaining_count; j++)
					remaining_length += strlen(remaining_tokens[j]) + 1;

				char *remaining_input = malloc(remaining_length + 1);
				remaining_input[0] = '\0';

				for (size_t j = 0; j < remaining_count; j++)
				{
					strcat(remaining_input, remaining_tokens[j]);
					if (j < remaining_count - 1)
						strcat(remaining_input, " ");
				}

				cmd->next = parse_input(remaining_input);
				free(remaining_input);
			}
			break;
		}
		else if (strcmp(tokens[i], "<") == 0)
		{
			// Input redirection
			if (i + 1 < token_count)
				cmd->input_file = ft_strdup(tokens[++i]);
			else
				fprintf(stderr, "Error: Missing input file after '<'\n");
		}
		else if (strcmp(tokens[i], ">") == 0)
		{
			// Output redirection
			if (i + 1 < token_count)
			{
				cmd->output_file = ft_strdup(tokens[++i]);
				cmd->append = 0; // Not append mode
			}
			else
				fprintf(stderr, "Error: Missing output file after '>'\n");
		}
		else if (strcmp(tokens[i], ">>") == 0)
		{
			// Append redirection
			if (i + 1 < token_count)
			{
				cmd->output_file = ft_strdup(tokens[++i]);
				cmd->append = 1; // Append mode
			}
			else
				fprintf(stderr, "Error: Missing output file after '>>'\n");
		}
		else
		{
			// Expand variables and store as argument
			char *expanded = expand_variables(tokens[i]);
			cmd->args[cmd->arg_count++] = expanded;
		}
	}
	cmd->args[cmd->arg_count] = NULL;
	// Free tokens
	for (size_t i = 0; i < token_count; i++)
		free(tokens[i]);
	free(tokens);
	return cmd;
}

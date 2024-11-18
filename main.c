/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:51:42 by hlyshchu          #+#    #+#             */
/*   Updated: 2024/11/18 16:02:18 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void handle_interactive_mode(void)
{
	char *input;

	printf("Interactive mode detected!\n");
	while (1)
	{
		input = readline("minishell> ");
		if (!input) // Handle Ctrl-D
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break;
		}
		if (*input)
		{
			add_history(input);
			t_command *cmd = parse_input(input);
			if (!cmd)
			{
				printf("Error: Failed to parse input.\n");
				free(input);
				continue;
			}

			printf("Parsed command:\n");
			for (size_t i = 0; i < cmd->arg_count; i++)		 // Use size_t for the loop variable
				printf("  arg[%zu]: %s\n", i, cmd->args[i]); // Use %zu for size_t
			if (cmd->input_file)
				printf("  Input redirection: %s\n", cmd->input_file);
			if (cmd->output_file)
				printf("  Output redirection: %s (append: %d)\n", cmd->output_file, cmd->append);

			// Debug pipeline
			t_command *next_cmd = cmd->next;
			while (next_cmd)
			{
				printf("Next Command:\n");
				for (size_t i = 0; i < next_cmd->arg_count; i++)
					printf("  arg[%zu]: %s\n", i, next_cmd->args[i]);

				if (next_cmd->input_file)
					printf("  Input redirection: %s\n", next_cmd->input_file);
				if (next_cmd->output_file)
					printf("  Output redirection: %s (append: %d)\n", next_cmd->output_file, next_cmd->append);

				next_cmd = next_cmd->next;
			}
			free_command(cmd);
		}
		free(input);
	}
}

void handle_non_interactive_mode(void)
{
	char buffer[1024];

	printf("Non-interactive mode detected!\n");
	while (fgets(buffer, sizeof(buffer), stdin))
	{
		buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
		if (buffer[0] != '\0')
		{
			printf("Processing input: %s\n", buffer);
			t_command *cmd = parse_input(buffer);
			if (!cmd)
			{
				printf("Error: Failed to parse input.\n");
				continue;
			}
			printf("Parsed command:\n");
			for (size_t i = 0; i < cmd->arg_count; i++)		 // Use size_t for the loop variable
				printf("  arg[%zu]: %s\n", i, cmd->args[i]); // Use %zu for size_t

			if (cmd->input_file)
				printf("  Input redirection: %s\n", cmd->input_file);
			if (cmd->output_file)
				printf("  Output redirection: %s (append: %d)\n", cmd->output_file, cmd->append);

			// Debug pipeline
			t_command *next_cmd = cmd->next;
			while (next_cmd)
			{
				printf("Next Command:\n");
				for (size_t i = 0; i < next_cmd->arg_count; i++)
					printf("  arg[%zu]: %s\n", i, next_cmd->args[i]);

				if (next_cmd->input_file)
					printf("  Input redirection: %s\n", next_cmd->input_file);
				if (next_cmd->output_file)
					printf("  Output redirection: %s (append: %d)\n", next_cmd->output_file, next_cmd->append);

				next_cmd = next_cmd->next;
			}
			free_command(cmd);
		}
	}
}

int main(void)
{
	is_interactive = isatty(STDIN_FILENO);
	setup_signals();

	if (is_interactive)
		handle_interactive_mode();
	else
		handle_non_interactive_mode();

	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:50:14 by root              #+#    #+#             */
/*   Updated: 2024/11/28 11:55:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <parse.h>
#include <unistd.h>

#define ERR_QUOTE "Error: Unclosed quotes\n"
#define ERR_PIPE_START "bash: syntax error near unexpected token `|'\n"
#define ERR_PIPE_END "Error: Unexpected end of input\n"
#define ERR_UNSUPPORTED "Error: Unsupported characters (||, &&, ;, \\)\n"
#define ERR_EMPTY_INPUT "Error: Input contains only spaces\n"

/**
 * @brief Checks if the string contains only whitespace characters.
 *
 * @param str
 * @return (int 1 if the string contains only whitespace characters);
 * 			0 otherwise.
 */
int	input_issspace(const char *str)
{
	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '\0')
	{
		(void)write(STDERR_FILENO, ERR_EMPTY_INPUT, sizeof(ERR_EMPTY_INPUT));
		return (-1);
	}
	else
		return (0);
}

static int	has_invalid_pipe_position(const char *str)
{
	const char	*end;

	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '|')
	{
		(void)write(STDERR_FILENO, ERR_PIPE_START, sizeof(ERR_PIPE_START) - 1);
		return (-1);
	}
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace(*end))
		end--;
	if (*end == '|')
	{
		(void)write(STDERR_FILENO, ERR_PIPE_END, sizeof(ERR_PIPE_END) - 1);
		return (-1);
	}
	return (0);
}

static int	contains_unsupported_characters(const char *str)
{
	enum e_quotes_type	quotes_type;

	quotes_type = no_quotes;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			ft_handle_quotes(*str, &quotes_type);
		if (quotes_type == no_quotes)
		{
			if (ft_strncmp(str, "||", 2) == 0 || ft_strncmp(str, "&&", 2) == 0)
			{
				(void)write(STDERR_FILENO, ERR_UNSUPPORTED,
					sizeof(ERR_UNSUPPORTED) - 1);
				return (-1);
			}
			else if (*str == ';' || *str == '\\')
			{
				(void)write(STDERR_FILENO, ERR_UNSUPPORTED,
					sizeof(ERR_UNSUPPORTED) - 1);
				return (-1);
			}
		}
		str++;
	}
	return (0);
}

/**
 * @brief Checks if the string contains:
 * 			unsupported characters (|| or &&)
 * 			ends/starts with a pipe;
 * 			have unclosed quotes;
 *
 *
 * @param str
 * @return int
 */
int	validate_input(const char *str)
{
	if (ft_check_arg_quotes(str) == -1)
	{
		(void)write(STDERR_FILENO, ERR_QUOTE, sizeof(ERR_QUOTE));
		return (-1);
	}
	if (has_invalid_pipe_position(str))
		return (-1);
	if (contains_unsupported_characters(str))
		return (-1);
	return (0);
}

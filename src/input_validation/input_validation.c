/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:50:14 by root              #+#    #+#             */
/*   Updated: 2024/12/01 00:16:04 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <parse.h>
#include <unistd.h>

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

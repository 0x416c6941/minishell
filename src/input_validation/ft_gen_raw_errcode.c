/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gen_raw_errcode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:50:03 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/10 11:48:46 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <utils.h>
#include <stddef.h>
#include <libft.h>

/**
 * Bypasses Norminete.
 * @brief	Checks $arg for unclosed quotes.
 * @param	arg	Argument to check.
 * @return	(UNCLOSED_SINGLE_QUOTE), if some single quote wasn't closed;
 * 			(UNCLOSED_DOUBLE_QUOTES), if some double quotes weren't closed;
 * 			(ARG_OK), if all quotes were closed.
 */
static int	ft_gen_quotes_status(const char *arg)
{
	enum e_quotes_type	quotes_type;

	quotes_type = no_quotes;
	while (*arg != '\0')
	{
		if (*arg == '\'' || *arg == '\"')
			ft_handle_quotes(*arg, &quotes_type);
		arg++;
	}
	if (quotes_type == single_quote)
		return (UNCLOSED_SINGLE_QUOTE);
	else if (quotes_type == double_quotes)
		return (UNCLOSED_DOUBLE_QUOTES);
	return (ARG_OK);
}

int	ft_gen_raw_errcode(const char *arg, enum e_arg_type arg_type)
{
	if (arg == NULL && arg_type == normal_arg)
		return (ARG_IS_EMPTY);
	else if (arg == NULL && arg_type == stdin_redir_arg)
		return (UNFINISHED_STDIN_REDIR);
	else if (arg == NULL && arg_type == stdout_redir_arg)
		return (UNFINISHED_STDOUT_REDIR);
	else if (arg_type != normal_arg
		&& (ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<<") == 0))
		return (INAPPROPRIATE_STDIN_REDIR);
	else if (arg_type != normal_arg
		&& (ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0))
		return (INAPPROPRIATE_STDOUT_REDIR);
	return (ft_gen_quotes_status(arg));
}

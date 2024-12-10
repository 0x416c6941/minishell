/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_are_there_syntax_errors_in_parsed_cmd.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:43:56 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/10 12:17:14 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <utils.h>
#include <stddef.h>
#include <parse.h>

int	ft_are_there_syntax_errors_in_parsed_cmd(const t_list *parsed_cmd)
{
	const t_ret	*cmd_status;

	while (parsed_cmd != NULL)
	{
		cmd_status = parsed_cmd->content;
		if (cmd_status->status == ARG_IS_EMPTY
			|| cmd_status->status == UNCLOSED_SINGLE_QUOTE
			|| cmd_status->status == UNCLOSED_DOUBLE_QUOTES
			|| cmd_status->status == UNFINISHED_STDIN_REDIR
			|| cmd_status->status == UNFINISHED_STDOUT_REDIR
			|| cmd_status->status == INAPPROPRIATE_STDIN_REDIR
			|| cmd_status->status == INAPPROPRIATE_STDOUT_REDIR
			|| cmd_status->status == AMBIGIOUS_REDIRECT)
		{
			if (ft_gen_errmsg(cmd_status->status, parsed_cmd->next) == -1)
				return (-1);
			return (1);
		}
		parsed_cmd = parsed_cmd->next;
	}
	return (0);
}

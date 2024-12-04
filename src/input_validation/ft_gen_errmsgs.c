/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gen_errmsgs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:54:55 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/04 19:35:55 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <libft.h>
#include <stddef.h>
#include <utils.h>
#include <parse.h>


/**
 * Second part of catching error codes and generating error messages.
 * @warning	Code is bad once again, but I don't care.
 * @param	errcode	Error code.
 * @return	(-1), if some write() to stderr failed;
 * 			(some non-negative value) otherwise (i.e. if everything went fine).
 */
static int	ft_gen_errmsg_part_two(int errcode)
{
	if (errcode == STAT_FAIL)
		return (ft_errmsg(STAT_FAIL_ERR));
	else if (errcode == PATHNAME_DOESNT_EXIST)
		return (ft_errmsg(PATHNAME_DOESNT_EXIST_ERR));
	else if (errcode == PATHNAME_IS_DIR)
		return (ft_errmsg(PATHNAME_IS_DIR_ERR));
	else if (errcode == PATHNAME_ISNT_EXECUTABLE)
		return (ft_errmsg(PATHNAME_ISNT_EXECUTABLE_ERR));
	else if (errcode == EXEC_ISNT_IN_PATH)
		return (ft_errmsg(EXEC_ISNT_IN_PATH_ERR));
	return (0);
}

/**
 * Generate an error message depending on value in $errcode
 * and if $next_node isn't NULL.
 * @warning	Code is bad, but I don't care.
 * @param	errcode		Error code.
 * @param	next_node	Next node in the list.
 * @return	(-1), if some write() to stderr failed;
 * 			(some non-negative value) otherwise (i.e. if everything went fine).
 */
static int	ft_gen_errmsg(int errcode, const t_list *next_node)
{
	if (errcode == ARG_IS_EMPTY && next_node != NULL)
		return (ft_errmsg(ERR_PIPE_START));
	else if (errcode == ARG_IS_EMPTY && next_node == NULL)
		return (ft_errmsg(ERR_PIPE_END));
	else if (errcode == UNCLOSED_SINGLE_QUOTE)
		return (ft_errmsg(UNCLOSED_SINGLE_QUOTE_ERR));
	else if (errcode == UNCLOSED_DOUBLE_QUOTES)
		return (ft_errmsg(UNCLOSED_DOUBLE_QUOTES_ERR));
	else if (errcode == UNFINISHED_STDIN_REDIR
		|| errcode == UNFINISHED_STDOUT_REDIR)
		return (ft_errmsg(UNFINISHED_REDIR_ERR));
	else if (errcode == INAPPROPRIATE_STDIN_REDIR)
		return (ft_errmsg(INAPPROPRIATE_STDIN_REDIR_ERR));
	else if (errcode == INAPPROPRIATE_STDOUT_REDIR)
		return (ft_errmsg(INAPPROPRIATE_STDOUT_REDIR_ERR));
	else if (errcode == AMBIGIOUS_REDIRECT)
		return (ft_errmsg(AMBIGIOUS_REDIR_ERR));
	return (ft_gen_errmsg_part_two(errcode));
}

int	ft_gen_errmsgs(const t_list *parsed_cmd)
{
	const t_ret	*cmd_status;

	while (parsed_cmd != NULL)
	{
		cmd_status = parsed_cmd->content;
		if (cmd_status->status != PATHNAME_IS_BUILTIN
			&& cmd_status->status != CMD_OK)
			if (ft_gen_errmsg(cmd_status->status, parsed_cmd->next) == -1)
				return (-1);
		parsed_cmd = parsed_cmd->next;
	}
	return (0);
}

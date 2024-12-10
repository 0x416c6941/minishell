/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gen_errmsg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:10:16 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/10 12:11:34 by asagymba         ###   ########.fr       */
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

int	ft_gen_errmsg(int errcode, const t_list *next_node)
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

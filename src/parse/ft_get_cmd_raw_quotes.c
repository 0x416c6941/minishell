/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_raw_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:40:16 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 19:33:04 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * Bypasses Norminette.
 * Processes stdin redirection argument and returns it as a node of t_list.
 * To be used only by ft_process_arg().
 * @param	arg			A pointer to a string containg current argument;
 * @param	arg_next	A pointer for further processing by
 * 						ft_get_next_arg().
 * @return	(-1), if something went really bad;
 * 			0, if argument is invalid;
 * 			Some positive value otherwise.
 */
static t_ret	ft_process_stdin_redir_arg(char **arg, char **arg_next)
{
	t_stdin_redir	*stdin_redir_arg;
	t_list			*ret;

	stdin_redir_arg = (t_stdin_redir *)malloc(sizeof(t_stdin_redir));
	if (stdin_redir_arg == NULL)
		return ((t_ret){(-1), NULL});
	ret = ft_lstnew(stdin_redir_arg);
	if (ret == NULL)
		return (ft_free_t_stdin_redir(stdin_redir_arg), (t_ret){(-1), NULL});
	if (ft_strcmp(*arg, "<<") == 0)
		stdin_redir_arg->redir_type = heredoc;
	else
		stdin_redir_arg->redir_type = file;
	*arg = ft_get_next_arg(NULL, arg_next);
	if (ft_check_arg_quotes(*arg) == -1)
		return (ft_lstclear(&ret, (void (*)(void *))ft_free_t_stdin_redir),
				(t_ret){0, NULL});
	*((char **)&(stdin_redir_arg->data)) = ft_strdup(*arg);
	if (stdin_redir_arg->data == NULL)
		return (ft_lstclear(&ret, (void (*)(void *))ft_free_t_stdin_redir),
				(t_ret){(-1), NULL});
	return ((t_ret){1, ret});
}

/**
 * Bypasses Norminette.
 * Processes stdout redirection argument and returns it as a node of t_list.
 * To be used only by ft_process_arg().
 * @param	arg			A pointer to a string containg current argument;
 * @param	arg_next	A pointer for further processing by
 * 						ft_get_next_arg().
 * @return	(-1), if something went really bad;
 * 			0, if argument is invalid;
 * 			Some positive value otherwise.
 */
static t_ret	ft_process_stdout_redir_arg(char **arg, char **arg_next)
{
	t_stdout_redir	*stdout_redir_arg;
	t_list			*ret;

	stdout_redir_arg = (t_stdout_redir *)malloc(sizeof(t_stdout_redir));
	if (stdout_redir_arg == NULL)
		return ((t_ret){(-1), NULL});
	ret = ft_lstnew(stdout_redir_arg);
	if (ret == NULL)
		return (ft_free_t_stdout_redir(stdout_redir_arg), (t_ret){(-1), NULL});
	if (ft_strcmp(*arg, ">>") == 0)
		stdout_redir_arg->redir_type = append;
	else
		stdout_redir_arg->redir_type = overwrite;
	*arg = ft_get_next_arg(NULL, arg_next);
	if (ft_check_arg_quotes(*arg) == -1)
		return (ft_lstclear(&ret, (void (*)(void *))ft_free_t_stdout_redir),
				(t_ret){0, NULL});
	*((char **)&(stdout_redir_arg->output_file)) = ft_strdup(*arg);
	if (stdout_redir_arg->output_file == NULL)
		return (ft_lstclear(&ret, (void (*)(void *))ft_free_t_stdout_redir),
				(t_ret){(-1), NULL});
	return ((t_ret){1, ret});
}

static t_ret	ft_process_regular_arg(char **arg)
{
	t_list	*ret;

	ret = ft_lstnew(NULL);
	if (ret == NULL)
		return ((t_ret){(-1), NULL});
	ret->content = ft_strdup(*arg);
	if (ret->content == NULL)
		return (ft_lstdelone(ret, free), (t_ret){(-1), NULL});
	return ((t_ret){1, ret});
}

/**
 * Bypasses Norminette.
 * Processes argument. Appends it either to
 * $stdin_redirs, $stdout_redirs or $args in $raw_cmd,
 * based on the type of argument.
 * @param	raw_cmd		A pointer to t_exec containing raw command.
 * @param	arg			A pointer to a string containg current argument;
 * @param	arg_next	A pointer for further processing by
 * 						ft_get_next_arg().
 * @return	(-1), if something went really bad;
 * 			0, if argument is invalid;
 * 			Some positive value otherwise.
 */
static int	ft_process_arg(t_exec *raw_cmd, char **arg, char **arg_next)
{
	t_ret	to_append;

	if (ft_strcmp(*arg, "<<") == 0 || ft_strcmp(*arg, "<") == 0)
	{
		to_append = ft_process_stdin_redir_arg(arg, arg_next);
		if (!(to_append.status > 0))
			return (to_append.status);
		ft_lstadd_back(&(raw_cmd->stdin_redirs), to_append.ret);
	}
	else if (ft_strcmp(*arg, ">>") == 0 || ft_strcmp(*arg, ">") == 0)
	{
		to_append = ft_process_stdout_redir_arg(arg, arg_next);
		if (!(to_append.status > 0))
			return (to_append.status);
		ft_lstadd_back(&(raw_cmd->stdout_redirs), to_append.ret);
	}
	else
	{
		to_append = ft_process_regular_arg(arg);
		if (!(to_append.status > 0))
			return (to_append.status);
		ft_lstadd_back(&(raw_cmd->args), to_append.ret);
	}
	return (1);
}

t_ret	ft_get_cmd_raw_quotes(char *token)
{
	t_exec	*ret;
	char	*arg;
	char	*arg_next;
	int		ft_process_arg_status;

	ret = ft_calloc(1, sizeof(t_exec));
	if (ret == NULL)
		return ((t_ret){(-1), NULL});
	arg = ft_get_next_arg(token, &arg_next);
	while (arg != NULL)
	{
		if (ft_check_arg_quotes(arg) == -1)
			return (ft_free_t_exec(ret), (t_ret){0, NULL});
		ft_process_arg_status = ft_process_arg(ret, &arg, &arg_next);
		if (!(ft_process_arg_status > 0))
			return (ft_free_t_exec(ret), (t_ret){ft_process_arg_status, NULL});
		arg = ft_get_next_arg(NULL, &arg_next);
	}
	return ((t_ret){0, ret});
}

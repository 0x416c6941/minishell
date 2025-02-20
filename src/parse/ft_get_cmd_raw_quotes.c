/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_raw_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:40:16 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/10 11:53:32 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <stdlib.h>
#include <stddef.h>
#include <utils.h>
#include <input_validation.h>

/**
 * Bypasses Norminette.
 * Processes stdin redirection argument and returns it as a node of t_list.
 * @warning	To be used only by ft_process_arg().
 * @warning	Dynamic memory allocation is used.
 * @param	arg			A pointer to a string containg current argument;
 * @param	arg_next	A pointer for further processing by
 * 						ft_get_next_arg().
 * @return	($status == (-1)) => something went really bad
 * 				($ret is NULL in this case);
 * 			($status != ARG_OK) => argument is invalid
 * 				($ret is NULL in this case);
 * 			otherwise $STATUS = ARG_OK and $ret is a node of t_list
 * 				containing stdin redirection argument.
 */
static t_ret	ft_process_stdin_redir_arg(t_ret *arg, char **arg_next)
{
	t_list	*ret;

	ret = ft_lstnew(NULL);
	if (ret == NULL)
		return ((t_ret){(-1), NULL});
	ret->content = ft_calloc(1, sizeof(t_stdin_redir));
	if (ret->content == NULL)
		return (ft_lstdelone(ret, free), (t_ret){(-1), NULL});
	if (ft_strcmp(arg->ret, "<<") == 0)
		((t_stdin_redir *)ret->content)->redir_type = heredoc;
	else
		((t_stdin_redir *)ret->content)->redir_type = file;
	free(arg->ret);
	*arg = ft_get_next_arg(NULL, arg_next);
	if (arg->status == -1)
		return (ft_lstdelone(ret, (void (*)(void *))ft_free_t_stdin_redir),
			(t_ret){(-1), NULL});
	else if (arg->ret == NULL || ft_check_arg(arg->ret, stdin_redir_arg) == -1)
		return (ft_lstdelone(ret, (void (*)(void *))ft_free_t_stdin_redir),
			(t_ret){ft_gen_raw_errcode(arg->ret, stdin_redir_arg), NULL});
	((t_stdin_redir *)ret->content)->data = ft_strdup(arg->ret);
	if (((t_stdin_redir *)ret->content)->data == NULL)
		return (ft_lstdelone(ret, (void (*)(void *))ft_free_t_stdin_redir),
			(t_ret){(-1), NULL});
	return ((t_ret){ARG_OK, ret});
}

/**
 * Bypasses Norminette.
 * Processes stdout redirection argument and returns it as a node of t_list.
 * @warning	To be used only by ft_process_arg().
 * @warning	Dynamic memory allocation is used.
 * @param	arg			A pointer to a string containg current argument;
 * @param	arg_next	A pointer for further processing by
 * 						ft_get_next_arg().
 * @return	($status == (-1)) => something went really bad
 * 				($ret is NULL in this case);
 * 			($status != ARG_OK) => argument is invalid
 * 				($ret is NULL in this case);
 * 			otherwise $STATUS = ARG_OK and $ret is a node of t_list
 * 				containing stdin redirection argument.
 */
static t_ret	ft_process_stdout_redir_arg(t_ret *arg, char **arg_next)
{
	t_list	*ret;

	ret = ft_lstnew(NULL);
	if (ret == NULL)
		return ((t_ret){(-1), NULL});
	ret->content = ft_calloc(1, sizeof(t_stdout_redir));
	if (ret->content == NULL)
		return (ft_lstdelone(ret, free), (t_ret){(-1), NULL});
	if (ft_strcmp(arg->ret, ">>") == 0)
		((t_stdout_redir *)ret->content)->redir_type = append;
	else
		((t_stdout_redir *)ret->content)->redir_type = overwrite;
	free(arg->ret);
	*arg = ft_get_next_arg(NULL, arg_next);
	if (arg->status == -1)
		return (ft_lstdelone(ret, (void (*)(void *))ft_free_t_stdout_redir),
			(t_ret){(-1), NULL});
	else if (arg->ret == NULL || ft_check_arg(arg->ret, stdout_redir_arg) == -1)
		return (ft_lstdelone(ret, (void (*)(void *))ft_free_t_stdout_redir),
			(t_ret){ft_gen_raw_errcode(arg->ret, stdout_redir_arg), NULL});
	((t_stdout_redir *)ret->content)->output_file = ft_strdup(arg->ret);
	if (((t_stdout_redir *)ret->content)->output_file == NULL)
		return (ft_lstdelone(ret, (void (*)(void *))ft_free_t_stdout_redir),
			(t_ret){(-1), NULL});
	return ((t_ret){ARG_OK, ret});
}

/**
 * Bypasses Norminette.
 * Processes normal argument and returns it as a node of t_list.
 * @warning	To be used only by ft_process_arg().
 * @warning	Dynamic memory allocation is used.
 * @param	arg			A pointer to a string containg current argument;
 * @param	arg_next	A pointer for further processing by
 * 						ft_get_next_arg().
 * @return	($status == (-1)) => something went really bad
 * 				($ret is NULL in this case);
 * 			($status != ARG_OK) => argument is invalid
 * 				($ret is NULL in this case);
 * 			otherwise $STATUS = ARG_OK and $ret is a node of t_list
 * 				containing stdin redirection argument.
 */
static t_ret	ft_process_regular_arg(t_ret *arg)
{
	t_list	*ret;

	if (arg->ret == NULL || ft_check_arg(arg->ret, normal_arg) == -1)
		return ((t_ret){ft_gen_raw_errcode(arg->ret, normal_arg), NULL});
	ret = ft_lstnew(NULL);
	if (ret == NULL)
		return ((t_ret){(-1), NULL});
	ret->content = ft_strdup(arg->ret);
	if (ret->content == NULL)
		return (ft_lstdelone(ret, free), (t_ret){(-1), NULL});
	return ((t_ret){ARG_OK, ret});
}

/**
 * Bypasses Norminette.
 * Processes argument. Appends it either to
 * $stdin_redirs, $stdout_redirs or $args in $raw_cmd,
 * based on the type of argument.
 * @param	raw_cmd		A pointer to t_exec containing raw command.
 * @param	arg			A pointer to value returned by ft_get_next_arg().
 * @param	arg_next	A pointer for further processing by
 * 						ft_get_next_arg().
 * @return	((-1), if something went really bad);
 * 			(ARG_OK), if argument was valid;
 * 			(some error code) otherwise.
 */
static int	ft_process_arg(t_exec *raw_cmd, t_ret *arg, char **arg_next)
{
	t_ret	to_append;

	if (ft_strcmp(arg->ret, "<<") == 0 || ft_strcmp(arg->ret, "<") == 0)
	{
		to_append = ft_process_stdin_redir_arg(arg, arg_next);
		if (to_append.status != ARG_OK)
			return (to_append.status);
		ft_lstadd_back(&(raw_cmd->stdin_redirs), to_append.ret);
	}
	else if (ft_strcmp(arg->ret, ">>") == 0 || ft_strcmp(arg->ret, ">") == 0)
	{
		to_append = ft_process_stdout_redir_arg(arg, arg_next);
		if (to_append.status != ARG_OK)
			return (to_append.status);
		ft_lstadd_back(&(raw_cmd->stdout_redirs), to_append.ret);
	}
	else
	{
		to_append = ft_process_regular_arg(arg);
		if (to_append.status != ARG_OK)
			return (to_append.status);
		ft_lstadd_back(&(raw_cmd->args), to_append.ret);
	}
	return (ARG_OK);
}

t_ret	ft_get_cmd_raw_quotes(char *token)
{
	t_exec	*ret;
	t_ret	arg;
	char	*saveptr_for_next_arg;
	int		ft_process_arg_status;

	ret = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (ret == NULL)
		return ((t_ret){(-1), NULL});
	arg = ft_get_next_arg(token, &saveptr_for_next_arg);
	if (arg.status == -1)
		return (ft_free_t_exec(ret), (t_ret){(-1), NULL});
	while (arg.ret != NULL)
	{
		ft_process_arg_status = ft_process_arg(ret, &arg,
				&saveptr_for_next_arg);
		free(arg.ret);
		if (ft_process_arg_status != ARG_OK)
			return (ft_free_t_exec(ret), (t_ret){ft_process_arg_status, NULL});
		arg = ft_get_next_arg(NULL, &saveptr_for_next_arg);
		if (arg.status == -1)
			return (ft_free_t_exec(ret), (t_ret){(-1), NULL});
	}
	if (ft_check_emptiness_raw(ret) == -1)
		return (ft_free_t_exec(ret), (t_ret){ARG_IS_EMPTY, NULL});
	return ((t_ret){CMD_OK, ret});
}

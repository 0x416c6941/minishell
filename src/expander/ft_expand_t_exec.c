/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_t_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:33:42 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/03 13:59:25 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * Expands $args in $exec_to_expand to $args_for_execve.
 * @brief	Norminette bypass.
 * @param	vars			Pointer to structure containing last exit status 
 * 							and environment variables in a key-pair structure.
 * @param	exec_to_expand	"t_exec" parsed command to expand.
 * @return	(-1), if something went wrong;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_expand_args_in_t_exec(const t_vars *vars,
		t_exec *exec_to_expand)
{
	size_t	i;
	t_list	*arg;
	t_ret	ft_dup_arg_expanded_status;

	i = 0;
	arg = exec_to_expand->args;
	while (arg != NULL)
	{
		ft_dup_arg_expanded_status = ft_dup_arg_expanded(vars,
				(char *)arg->content);
		if (ft_dup_arg_expanded_status.status == -1)
			return (-1);
		exec_to_expand->args_for_execve[i++] = ft_dup_arg_expanded_status.ret;
		arg = arg->next;
	}
	return (0);
}

/**
 * Expands $stdin_redirs in $exec_to_expand.
 * 	Old unexpanded string versions will be freed.
 * @brief	Norminette bypass.
 * @param	vars			Pointer to structure containing last exit status 
 * 							and environment variables in a key-pair structure.
 * @param	exec_to_expand	"t_exec" parsed command to expand.
 * @return	(-1), if something went wrong;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_expand_stdin_redirs_in_t_exec(const t_vars *vars,
		t_exec *exec_to_expand)
{
	t_list	*stdin_redir;
	t_ret	ft_dup_arg_expanded_status;

	stdin_redir = exec_to_expand->stdin_redirs;
	while (stdin_redir != NULL)
	{
		ft_dup_arg_expanded_status = ft_dup_arg_expanded(vars,
				((t_stdin_redir *)stdin_redir->content)->data);
		if (ft_dup_arg_expanded_status.status == -1)
			return (-1);
		free((char *)(((t_stdin_redir *)stdin_redir->content)->data));
		((t_stdin_redir *)stdin_redir->content)->data
			= ft_dup_arg_expanded_status.ret;
		stdin_redir = stdin_redir->next;
	}
	return (0);
}

/**
 * Expands $stdout_redirs in $exec_to_expand.
 * 	Old unexpanded string versions will be freed.
 * @brief	Norminette bypass.
 * @param	vars			Pointer to structure containing last exit status 
 * 							and environment variables in a key-pair structure.
 * @param	exec_to_expand	"t_exec" parsed command to expand.
 * @return	(-1), if something went wrong;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_expand_stdout_redirs_in_t_exec(const t_vars *vars,
		t_exec *exec_to_expand)
{
	t_list	*stdout_redir;
	t_ret	ft_dup_arg_expanded_status;

	stdout_redir = exec_to_expand->stdout_redirs;
	while (stdout_redir != NULL)
	{
		ft_dup_arg_expanded_status = ft_dup_arg_expanded(vars,
				((t_stdout_redir *)stdout_redir->content)->output_file);
		if (ft_dup_arg_expanded_status.status == -1)
			return (-1);
		free((char *)(((t_stdout_redir *)stdout_redir->content)->output_file));
		((t_stdout_redir *)stdout_redir->content)->output_file
			= ft_dup_arg_expanded_status.ret;
		stdout_redir = stdout_redir->next;
	}
	return (0);
}

/**
 * Cast of ft_lstsize() return value to size_t in ft_calloc() call isn't good.
 * But I don't care.
 */
int	ft_expand_t_exec(const t_vars *vars, t_exec *exec_to_expand)
{
	exec_to_expand->args_for_execve = (char **)ft_calloc(sizeof(char *),
			(size_t)(ft_lstsize(exec_to_expand->args) + 1));
	if (exec_to_expand->args_for_execve == NULL
		|| ft_expand_args_in_t_exec(vars, exec_to_expand) == -1)
		return (-1);
	ft_lstclear(&exec_to_expand->args, free);
	if (ft_expand_stdin_redirs_in_t_exec(vars, exec_to_expand) == -1
		|| ft_expand_stdout_redirs_in_t_exec(vars, exec_to_expand) == -1)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:26:45 by root              #+#    #+#             */
/*   Updated: 2024/11/29 15:50:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"
#include <expander.h>
#include <parse.h>
#include <stdlib.h>

static int	initialize_args_for_execve(t_exec *cmd)
{
	size_t	arg_count;

	if (!cmd || !cmd->args)
		return (0);
	arg_count = (size_t)ft_lstsize(cmd->args);
	cmd->args_for_execve = ft_calloc(arg_count + 1, sizeof(char *));
	if (!cmd->args_for_execve)
		return (-1);
	return (1);
}

static int	process_arguments(t_exec *cmd)
{
	t_list	*temp_args;
	t_ret	*result;
	size_t	i;

	temp_args = cmd->args;
	i = 0;
	while (temp_args)
	{
		result = ft_process_args((const char *)temp_args->content);
		if (!result || result->status == -1)
			return (-1);
		cmd->args_for_execve[i] = (char *)result->ret;
		free(result);
		temp_args = temp_args->next;
		i++;
	}
	cmd->args_for_execve[i] = NULL;
	return (1);
}

static int	process_redirections(t_exec *cmd)
{
	(void)cmd;
	// if ((ft_process_stdin_redirs(cmd->stdin_redirs) == -1)
	// 	|| (ft_process_stdout_redirs(cmd->stdout_redirs) == -1))
	// 	return (-1);
	return (1);
}

int	expand(t_exec *cmd)
{
	if (initialize_args_for_execve(cmd) == -1)
		return (-1);
	if (process_arguments(cmd) == -1)
		return (-1);
	if (process_redirections(cmd) == -1)
		return (-1);
	return (1);
}

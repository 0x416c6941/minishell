/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:20:53 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/15 16:18:51 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <builtins.h>

int	ft_exec_builtin(t_minishell_data *data, t_exec *cmd)
{
	if (ft_strcmp(cmd->args_for_execve[0], "echo") == 0)
		return (echo_builtin(data, (const char **)(cmd->args_for_execve + 1)));
	else if (ft_strcmp(cmd->args_for_execve[0], "pwd") == 0)
		return (pwd_builtin(data, (const char **)(cmd->args_for_execve + 1)));
	else if (ft_strcmp(cmd->args_for_execve[0], "export") == 0)
		return (export_builtin(data,
				(const char **)(cmd->args_for_execve + 1)));
	else if (ft_strcmp(cmd->args_for_execve[0], "unset") == 0)
		return (unset_builtin(data, (const char **)(cmd->args_for_execve + 1)));
	else if (ft_strcmp(cmd->args_for_execve[0], "env") == 0)
		return (env_builtin(data, (const char **)(cmd->args_for_execve + 1)));
	else if (ft_strcmp(cmd->args_for_execve[0], "exit") == 0)
		return (exit_builtin(data, (const char **)(cmd->args_for_execve + 1)));
	return (0);
}

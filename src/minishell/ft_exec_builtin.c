/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:20:53 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/16 02:41:14 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <builtins.h>

#define HOW_DID_WE_GET_HERE	2147438647

int	ft_exec_builtin(t_minishell_data *data, t_exec *cmd)
{
	if (ft_strcmp(cmd->args_for_execve[0], "echo") == 0)
		return (echo_builtin(data, (const char **)(cmd->args_for_execve + 1)));
	if (ft_strcmp(cmd->args_for_execve[0], "cd") == 0)
		return (cd_builtin(data, (const char **)(cmd->args_for_execve + 1)));
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
	{
		if (exit_builtin(data,
					(const char **)(cmd->args_for_execve + 1)) == EXIT_OK)
			return (data->with_which_code);
		else
			return (EXIT_ERROR);
	}
	return (HOW_DID_WE_GET_HERE);
}

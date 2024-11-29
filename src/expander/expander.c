/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:26:45 by root              #+#    #+#             */
/*   Updated: 2024/11/29 14:53:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <parse.h>

int	expand(t_exec *cmd)
{
	size_t	arg_count;
	size_t	i;
	t_list	*temp_args;
	t_ret	*result;

	if (!cmd || !cmd->args)
		return (0);
	i = 0;
	arg_count = (size_t)ft_lstsize(cmd->args);
	cmd->args_for_execve = ft_calloc(arg_count + 1, sizeof(char *));
	if (!cmd->args_for_execve)
		return (-1);
	temp_args = cmd->args;
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
	// if ((ft_process_stdin_redirs(cmd->stdin_redirs) == -1)
	// 	|| (ft_process_stdout_redirs(cmd->stdout_redirs) == -1))
	// 	return (-1);
	return (1);
}

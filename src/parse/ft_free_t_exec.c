/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_t_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:53:09 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/14 20:16:16 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stdlib.h>
#include <libft.h>
#include <unistd.h>

void	ft_free_t_exec(t_exec *exec)
{
	if (exec == NULL)
		return ;
	free((char *)(exec->path_to_exec));
	ft_lstclear(&(exec->args), free);
	ft_free_args_for_execve(&(exec->args_for_execve));
	ft_lstclear(&(exec->stdin_redirs), (void (*)(void *))ft_free_t_stdin_redir);
	if (exec->stdin_redir.is_initialized)
		close(exec->stdin_redir.fd);
	if (exec->stdout_redir.is_initialized)
		close(exec->stdout_redir.fd);
	ft_lstclear(&(exec->stdout_redirs),
		(void (*)(void *))ft_free_t_stdout_redir);
	free(exec);
}

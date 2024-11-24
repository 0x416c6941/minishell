/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_t_execs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:53:09 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 14:21:01 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <stdlib.h>

void	ft_free_t_execs(t_exec **exec)
{
	t_exec	*next;

	while (*exec != NULL)
	{
		free((char *)((*exec)->path_to_exec));
		ft_free_t_args(&((*exec)->args));
		ft_free_args_for_execve(&((*exec)->args_for_execve));
		ft_free_t_stdin_redirs(&((*exec)->stdin_redirs));
		ft_free_t_stdout_redirs(&((*exec)->stdout_redirs));
		next = (*exec)->next;
		free(*exec);
		*exec = next;
	}
}

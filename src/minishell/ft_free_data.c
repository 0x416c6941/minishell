/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:06:52 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/14 23:47:30 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <utils.h>
#include <stddef.h>
#include <parse.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define CLOSE_FAILED	"ft_free_data():: close() failed\n"

int	ft_free_data(t_minishell_data *data)
{
	ft_lstclear(&data->vars.envs, (void (*)(void *))ft_free_t_env);
	ft_lstclear((t_list **)&data->parser_result,
		(void (*)(void *))ft_free_t_ret_with_t_exec);
	if (data->real_stdin_fd != -1)
	{
		if (close(data->real_stdin_fd) == -1)
			return (ft_errmsg(CLOSE_FAILED), -1);
	}
	if (data->real_stdout_fd != -1)
	{
		if (close(data->real_stdout_fd) == -1)
			return (ft_errmsg(CLOSE_FAILED), -1);
	}
	rl_clear_history();
	return (0);
}

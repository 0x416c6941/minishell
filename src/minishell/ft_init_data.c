/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:48:37 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/16 01:05:28 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <utils.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>

int	ft_init_data(const char **envp, t_minishell_data *data)
{
	t_ret	status;

	(void)ft_memset(data, 0, sizeof(t_minishell_data));
	data->real_stdin_fd = -1;
	data->real_stdout_fd = -1;
	status = ft_initialize_envs(envp);
	if (status.status == -1)
		return (-1);
	data->vars.last_exit_status = 0;
	data->vars.envs = status.ret;
	*((bool *)(&data->is_interactive)) = isatty(STDIN_FILENO);
	data->parser_result = NULL;
	data->real_stdin_fd = dup(STDIN_FILENO);
	if (data->real_stdin_fd == -1)
		return (-1);
	data->real_stdout_fd = dup(STDOUT_FILENO);
	if (data->real_stdout_fd == -1)
		return ((void)close(data->real_stdin_fd), data->real_stdin_fd = -1, -1);
	data->should_leave = false;
	data->with_which_code = -1;
	return (0);
}

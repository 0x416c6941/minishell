/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:48:37 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/14 20:26:41 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>

int		ft_init_data(const char **envp, t_minishell_data *data)
{
	t_ret	status;

	status = ft_initialize_envs(envp);
	if (status.status == -1)
		return (-1);
	data->vars.last_exit_status = 0;
	data->vars.envs = status.ret;
	*((bool *)(&data->is_interactive)) = isatty(STDIN_FILENO);
	data->parser_result.status = -1;
	data->parser_result.ret = NULL;
	data->should_leave = false;
	data->with_which_code = -1;
	return (0);
}

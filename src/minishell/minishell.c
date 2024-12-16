/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:33:48 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/16 14:46:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <stdbool.h>

int	minishell(t_minishell_data *data)
{
	int	status;

	while (42)
	{
		if (data->is_interactive)
		{
			status = handle_signal_interactive();
			if (status == -1)
				return (data->should_leave = true,
					data->with_which_code = MESSED_UP, -1);
		}
		status = ft_get_execs(data);
		if (status == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, -1);
		else if (status == MINISHELL_INPUT_INCORRECT)
			continue ;
		else if (status == MINISHELL_INPUT_EOF)
			return (data->should_leave = true, data->with_which_code = 0, 0);
		status = handle_signal_noninteractive();
		if (status == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, -1);
		ft_check_syntax_and_execute(data);
		if (data->should_leave)
		{
			if (data->with_which_code == MESSED_UP)
				return (1);
			return (0);
		}
	}
}

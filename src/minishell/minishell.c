/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:33:48 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/15 00:17:46 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdbool.h>
#include <parse.h>

int	minishell(t_minishell_data *data)
{
	int	status;

	while (42)
	{
		if (data->is_interactive)
			(void)data; // SET INTERACTIVE MODE HERE
		status = ft_get_execs(data);
		if (status == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, -1);
		else if (status == MINISHELL_INPUT_INCORRECT)
			continue ;
		else if (status == MINISHELL_INPUT_EOF)
			return (data->should_leave = true,
				data->with_which_code = 0, 0);
		// SET NON-INTERACTIVE MODE HERE
		ft_check_syntax_and_execute(data);
		if (data->should_leave)
		{
			if (data->with_which_code == MESSED_UP)
				return (1);
			return (0);
		}
	}
}

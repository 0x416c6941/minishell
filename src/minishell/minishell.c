/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:33:48 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/14 21:43:12 by asagymba         ###   ########.fr       */
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
		{
			// Set interactive mode
		}
		status = ft_get_execs(data);
		if (status == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, -1);
		else if (status == MINISHELL_INPUT_INCORRECT)
			continue ;
		else if (status == MINISHELL_INPUT_EOF)
			return (data->should_leave = true,
				data->with_which_code = 0, 0);
		// set noninteractive mode
		// handle heredocs and exec I guess?.
		ft_lstclear((t_list **)&data->parser_result,
			(void (*)(void *))ft_free_t_ret_with_t_exec);
	}
}

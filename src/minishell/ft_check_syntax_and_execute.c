/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax_and_execute.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:56:12 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/16 02:23:43 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <input_validation.h>
#include <stdbool.h>
#include <libft.h>
#include <parse.h>

void	ft_check_syntax_and_execute(t_minishell_data *data)
{
	int	status;

	status = ft_are_there_syntax_errors_in_parsed_cmd(data->parser_result);
	if (status == -1 || status > 0)
	{
		if (status == -1)
		{
			data->should_leave = true;
			data->with_which_code = MESSED_UP;
		}
		ft_lstclear(&data->parser_result,
			(void (*)(void *))ft_free_t_ret_with_t_exec);
		return ;
	}
	status = ft_execute(data);
	if (status == -1)
	{
		data->should_leave = true;
		data->with_which_code = MESSED_UP;
	}
	ft_lstclear(&data->parser_result,
		(void (*)(void *))ft_free_t_ret_with_t_exec);
}

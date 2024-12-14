/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:06:52 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/14 21:39:33 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <utils.h>
#include <stddef.h>
#include <parse.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_free_data(t_minishell_data *data)
{
	ft_lstclear(&data->vars.envs, (void (*)(void *))ft_free_t_env);
	ft_lstclear((t_list **)&data->parser_result,
		(void (*)(void *))ft_free_t_ret_with_t_exec);
	rl_clear_history();
}

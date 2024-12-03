/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_t_ret_with_t_exec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:21:31 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/03 17:22:28 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <utils.h>
#include <stddef.h>
#include <stdlib.h>

void	ft_free_t_ret_with_t_exec(t_ret *t_ret_with_t_exec)
{
	if (t_ret_with_t_exec == NULL)
		return ;
	ft_free_t_exec(t_ret_with_t_exec->ret);
	free(t_ret_with_t_exec);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_t_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:53:09 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 14:05:41 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <stdlib.h>

void	ft_free_t_args(t_arg **arg)
{
	t_arg	*next;

	while (*arg != NULL)
	{
		free((*arg)->arg);
		next = (*arg)->next;
		free(*arg);
		*arg = next;
	}
}

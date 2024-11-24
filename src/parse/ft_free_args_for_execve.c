/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_args_for_execve.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:53:09 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 14:11:12 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <stdlib.h>

void	ft_free_args_for_execve(char ***arg_for_execve)
{
	size_t	i;

	i = 0;
	while (*(*arg_for_execve + i) != NULL)
		free(*(*arg_for_execve + i++));
	free(*arg_for_execve);
	*arg_for_execve = NULL;
}

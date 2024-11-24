/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_args_for_execve.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:53:09 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 19:37:07 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <stdlib.h>

void	ft_free_args_for_execve(char ***args_for_execve)
{
	size_t	i;

	if (*args_for_execve == NULL)
		return ;
	i = 0;
	while (*(*args_for_execve + i) != NULL)
		free(*(*args_for_execve + i++));
	free(*args_for_execve);
	*args_for_execve = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:53:23 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/01 00:55:04 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

int	ft_is_builtin(const char *arg)
{
	if (ft_strcmp(arg, "echo") == 0 || ft_strcmp(arg, "cd") == 0
		|| ft_strcmp(arg, "pwd") == 0 || ft_strcmp(arg, "export") == 0
		|| ft_strcmp(arg, "unset") == 0 || ft_strcmp(arg, "env") == 0
		|| ft_strcmp(arg, "exit") == 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:03:05 by root              #+#    #+#             */
/*   Updated: 2024/11/29 14:04:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*ft_getenv(const char *name)
{
	char	*res;
	char	*exit_code_str;

	if (!name)
		return (ft_strdup(""));
	if (ft_strcmp(name, "?") == 0)
	{
		exit_code_str = ft_itoa(g_exit_code);
		return (ft_strdup(exit_code_str));
	}
	res = getenv(name);
	if (!res)
		return (ft_strdup(""));
	return (ft_strdup(res));
}

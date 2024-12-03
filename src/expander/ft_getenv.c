/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:55:25 by root              #+#    #+#             */
/*   Updated: 2024/12/03 11:07:36 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <utils.h>
#include <stddef.h>
#include <stdlib.h>

char	*ft_getenv(const t_vars *vars, const char *name)
{
	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(g_exit_code));
	env = getenv(name);
	if (res == NULL)
		return (ft_strdup(""));
	return (ft_strdup(env));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_invalid_pipe_position.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:50:14 by root              #+#    #+#             */
/*   Updated: 2024/12/04 19:36:36 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <parse.h>
#include <unistd.h>

int	ft_has_invalid_pipe_position(const char *str)
{
	const char	*end;

	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '|')
	{
		if (ft_errmsg(ERR_PIPE_START) == -1)
			return (-1);
		return (0);
	}
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace(*end))
		end--;
	if (*end == '|')
	{
		if (ft_errmsg(ERR_PIPE_END) == -1)
			return (-1);
		return (0);
	}
	return (1);
}

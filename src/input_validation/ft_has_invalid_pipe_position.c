/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:50:14 by root              #+#    #+#             */
/*   Updated: 2024/12/04 19:23:03 by asagymba         ###   ########.fr       */
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
		(void)ft_errmsg(ERR_PIPE_START);
		return (-1);
	}
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace(*end))
		end--;
	if (*end == '|')
	{
		(void)ft_errmsg(ERR_PIPE_END);
		return (-1);
	}
	return (0);
}

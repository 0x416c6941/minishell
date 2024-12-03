/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_issspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:50:14 by root              #+#    #+#             */
/*   Updated: 2024/12/03 16:05:01 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <libft.h>

int	ft_input_issspace(const char *str)
{
	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

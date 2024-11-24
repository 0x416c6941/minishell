/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_part1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:23:45 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 12:25:57 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

/**
 * The first part of while condition doesn't make any sense,
 * but let's let it be :p
 */
void	ft_skip_spaces(const char **str)
{
	while (**str != '\0' && **str == ' ')
		(*str)++;
}

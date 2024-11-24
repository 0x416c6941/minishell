/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:00:11 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 12:32:18 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <utils.h>

char	*ft_get_next_token(char *prompt, char **saveptr)
{
	char	*ret;

	if (prompt != NULL)
		*saveptr = prompt;
	ret = *saveptr;
	if (*ret == '\0')
		return (NULL);
	while (**saveptr != '\0')
	{
		if (**saveptr == '|')
		{
			*(*saveptr)++ = '\0';
			break ;
		}
		(*saveptr)++;
	}
	return (ret);
}

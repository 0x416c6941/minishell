/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:00:11 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/10 15:08:10 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <utils.h>

char	*ft_get_next_token(char *prompt, char **saveptr)
{
	char				*ret;
	enum e_quotes_type	quotes;

	if (prompt != NULL)
		*saveptr = prompt;
	ret = *saveptr;
	if (*ret == '\0')
		return (NULL);
	quotes = no_quotes;
	while (**saveptr != '\0')
	{
		if (**saveptr == '\'' || **saveptr == '\"')
			ft_handle_quotes(**saveptr, &quotes);
		else if (**saveptr == '|' && quotes == no_quotes)
		{
			*(*saveptr)++ = '\0';
			break ;
		}
		(*saveptr)++;
	}
	return (ret);
}

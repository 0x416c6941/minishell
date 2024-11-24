/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:48:55 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 13:03:17 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <utils.h>

char	*ft_get_next_arg(char *token, char **saveptr)
{
	enum e_quotes_type	quotes;
	char				*ret;

	quotes = no_quotes;
	if (token != NULL)
		*saveptr = token;
	ft_skip_spaces((const char **)saveptr);
	ret = *saveptr;
	if (*ret == '\0')
		return (NULL);
	while (**saveptr != '\0')
	{
		if (**saveptr == '\'' || **saveptr == '\"')
			ft_handle_quotes(**saveptr, &quotes);
		else if (**saveptr == ' ' && quotes == no_quotes)
		{
			*(*saveptr)++ = '\0';
			break ;
		}
		(*saveptr)++;
	}
	return (ret);
}

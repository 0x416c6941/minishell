/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:58:38 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 13:02:24 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

void	ft_handle_quotes(char quote, enum e_quotes_type *quotes_type)
{
	if (quote == '\'')
	{
		if (*quotes_type == no_quotes)
			*quotes_type = single_quote;
		else if (*quotes_type == single_quote)
			*quotes_type = no_quotes;
	}
	else if (quote == '\"')
	{
		if (*quotes_type == no_quotes)
			*quotes_type = double_quotes;
		else if (*quotes_type == double_quotes)
			*quotes_type = no_quotes;
	}
}

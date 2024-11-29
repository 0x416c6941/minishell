/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:44:21 by root              #+#    #+#             */
/*   Updated: 2024/11/29 16:44:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

/**
 * @brief Removes outer quotes from the string and copies the content
 *		into `dest`.
 *
 * @param dest Pointer to the destination buffer.
 * @param src Pointer to the source string.
 */
void	remove_quotes(char *dest, const char *src)
{
	char	outer_quote;

	if (!src || !dest)
		return ;
	outer_quote = *src;
	if (outer_quote != '\'' && outer_quote != '\"')
	{
		ft_strcpy(dest, src);
		return ;
	}
	src++;
	while (*src && *src != outer_quote)
		*dest++ = *src++;
	*dest = '\0';
}

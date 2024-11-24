/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:09:32 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 13:17:00 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	ft_check_arg_quotes(const char *arg)
{
	enum e_quotes_type	quotes_type;

	quotes_type = no_quotes;
	while (*arg != '\0')
	{
		if (*arg == '\'' || *arg == '\"')
			ft_handle_quotes(*arg, &quotes_type);
		arg++;
	}
	if (quotes_type != no_quotes)
		return (-1);
	return (0);
}

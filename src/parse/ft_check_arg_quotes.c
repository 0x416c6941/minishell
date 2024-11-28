/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:09:32 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/28 11:14:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int ft_check_arg_quotes(const char *arg)
{
	enum e_quotes_type quotes_type;

	quotes_type = no_quotes;
	while (arg && *arg != '\0')
	{
		if (*arg == '\'' || *arg == '\"')
			ft_handle_quotes(*arg, &quotes_type);
		arg++;
	}
	if (quotes_type != no_quotes)
		return (-1);
	return (0);
}

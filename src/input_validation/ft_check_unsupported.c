/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_unsupported.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:50:14 by root              #+#    #+#             */
/*   Updated: 2024/12/10 11:46:38 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <utils.h>
#include <libft.h>

int	ft_check_unsupported(const char *str)
{
	enum e_quotes_type	quotes_type;

	quotes_type = no_quotes;
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '\"')
			ft_handle_quotes(*str, &quotes_type);
		if (quotes_type == no_quotes)
		{
			if (*str == '&' || *str == ';' || *str == '\\'
				|| ft_strncmp(str, "||", sizeof("||") - 1) == 0
				|| ft_strncmp(str, "&&", sizeof("&&") - 1) == 0)
			{
				if (ft_errmsg(ERR_UNSUPPORTED) == -1)
					return (-1);
				return (0);
			}
		}
		str++;
	}
	return (1);
}

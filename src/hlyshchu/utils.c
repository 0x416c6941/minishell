/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:51:40 by root              #+#    #+#             */
/*   Updated: 2024/11/17 18:59:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ft_isspace(const char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool check_unclosed_quotes(const char *str)
{
	bool inside_single_quote;
	bool inside_double_quote;
	int i;

	inside_single_quote = false;
	inside_double_quote = false;
	i = -1;
	if (!str)
		return false;
	while (str[++i] != '\0')
	{
		if (str[i] == '\\' && str[i + 1] && (str[i + 1] == '\'' || str[i + 1] == '"'))
			i++;
		else if (str[i] == '\'' && !inside_double_quote)
			inside_single_quote = !inside_single_quote;
		else if (str[i] == '"' && !inside_single_quote)
			inside_double_quote = !inside_double_quote;
	}
	return inside_single_quote || inside_double_quote;
}

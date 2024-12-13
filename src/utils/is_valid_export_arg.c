/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_export_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:07:18 by root              #+#    #+#             */
/*   Updated: 2024/12/13 19:01:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <utils.h>

bool	is_valid_export_arg(const char *arg)
{
	const char	*c;

	c = arg;
	if (!arg || ft_strchr(arg, '=') == NULL)
		return (false);
	if (!(arg[0] == '_' || ft_isalpha(arg[0])))
		return (false);
	while (*c != '=')
	{
		if (!(ft_isalnum(*c) || *c == '_'))
			return (false);
		c++;
	}
	return (true);
}

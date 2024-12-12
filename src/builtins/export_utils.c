/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:30:29 by root              #+#    #+#             */
/*   Updated: 2024/12/12 17:30:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

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
		if (!(isalnum(*c) || *c == '_'))
			return (false);
		c++;
	}
	return (true);
}

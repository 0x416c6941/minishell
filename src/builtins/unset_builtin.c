/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:59:34 by root              #+#    #+#             */
/*   Updated: 2024/12/13 15:15:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

int	unset_builtin(t_vars *vars, const char **args)
{
	if (!vars || !args)
		return (EXIT_FATAL_ERROR);
	if (!args || !*args)
		return (EXIT_OK);
	while (*args)
	{
		if (!is_valid_export_arg(*args))
		{
			/* code */
		}
	}

	return (EXIT_OK);
}
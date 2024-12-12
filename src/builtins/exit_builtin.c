/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:21:24 by root              #+#    #+#             */
/*   Updated: 2024/12/12 17:47:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

/**
 * @brief Exits the shell.
 * NEED TO SET GLOBAL EXIT CODE LATER
 */
int	exit_builtin(const char *args[])
{
	if (!args)
		return (EXIT_SUCCESS);
	if (args[1])
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
}

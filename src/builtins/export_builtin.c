/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:29:58 by root              #+#    #+#             */
/*   Updated: 2024/12/15 14:08:01 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

int	export_builtin(t_minishell_data *data, const char *args[])
{
	t_env	*saved;

	i = 0;
	while (args[i] != NULL)
	{
		if (!is_valid_export_arg(args[i]))
		{
			export_err_msg(args[i]);
			i++;
			continue ;
		}
		if (add_env(env_head, args[i]) != EXIT_OK)
			return (EXIT_FATAL_ERROR);
		i++;
	}
	return (EXIT_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:28:16 by root              #+#    #+#             */
/*   Updated: 2024/12/12 17:28:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

#define EXPORT_ERROR "export: failed to add or update variable\n"

static int	write_env_variable(const char *prefix, t_env *env)
{
	if (write(1, prefix, ft_strlen(prefix)) == -1)
		return (EXIT_FAILURE);
	if (write(1, env->key, ft_strlen(env->key)) == -1)
		return (EXIT_FAILURE);
	if (env->value)
	{
		if (write(1, "=\"", 2) == -1)
			return (EXIT_FAILURE);
		if (write(1, env->value, ft_strlen(env->value)) == -1)
			return (EXIT_FAILURE);
		if (write(1, "\"", 1) == -1)
			return (EXIT_FAILURE);
	}
	if (write(1, "\n", 1) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	export_no_args_builtin(t_vars *vars)
{
	const char	*prefix;
	t_list		*current;
	t_env		*env;

	prefix = "declare -x ";
	current = vars->envs;
	while (current)
	{
		env = (t_env *)current->content;
		if (write_env_variable(prefix, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

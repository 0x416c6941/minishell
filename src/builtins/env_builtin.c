/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:16:19 by root              #+#    #+#             */
/*   Updated: 2024/12/14 10:29:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

/**
 * @brief Prints the environment variables stored in the t_vars structure.
 *
 * This function iterates through the linked list of environment variables
 * in the `t_vars` structure and prints each variable's key and value to
 * standard output in the format: key=value. If a key exists without a value,
 * only the key is printed. If the `vars` parameter is NULL or contains no
 * environment variables, the function returns EXIT_FATAL_ERROR. Otherwise, it
 * returns EXIT_OK.
 *
 * @param vars A pointer to the t_vars structure containing the environment
 *             variables to be printed.
 * @return int EXIT_OK on success, EXIT_FATAL_ERROR if `vars` is invalid.
 */

int	env_builtin(t_vars *vars)
{
	t_list	*current;
	t_env	*env;

	if (!vars || !vars->envs)
		return (EXIT_FATAL_ERROR);
	current = vars->envs;
	while (current)
	{
		if (current->content)
		{
			env = (t_env *)current->content;
			if (env->key)
			{
				if (write(STDOUT_FILENO, env->key, ft_strlen(env->key)) == -1)
					return (EXIT_FATAL_ERROR);
				if (env->value)
				{
					if (write(STDOUT_FILENO, "=", 1) == -1
						|| write(STDOUT_FILENO, env->value,
							ft_strlen(env->value)) == -1 || write(STDOUT_FILENO,
							"\n", 1) == -1)
						return (EXIT_FATAL_ERROR);
				}
				else if (write(STDOUT_FILENO, "\n", 1) == -1)
					return (EXIT_FATAL_ERROR);
			}
		}
		current = current->next;
	}
	return (EXIT_OK);
}

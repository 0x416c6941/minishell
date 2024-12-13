/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:16:19 by root              #+#    #+#             */
/*   Updated: 2024/12/13 15:15:08 by root             ###   ########.fr       */
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
				ft_printf("%s", env->key);
				if (env->value)
					ft_printf("=%s", env->value);
				ft_printf("\n");
			}
		}
		current = current->next;
	}
	return (EXIT_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:59:34 by root              #+#    #+#             */
/*   Updated: 2024/12/13 17:38:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

/**
 * Removes an environment variable from the list.
 *
 * @param envs - a pointer to the linked list of environment variables
 * @param key - the key of the variable to remove
 * @return EXIT_OK on success and if key is not found
 */
static int	remove_env(t_list **envs, const char *key)
{
	t_list	*current;
	t_list	*prev;
	t_env	*env;

	current = *envs;
	prev = NULL;
	while (current)
	{
		env = (t_env *)current->content;
		if (env && env->key && ft_strcmp(env->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*envs = current->next;
			free(env->key);
			free(env->value);
			free(env);
			free(current);
			return (EXIT_OK);
		}
		prev = current;
		current = current->next;
	}
	return (EXIT_OK);
}
/**
 * Unsets one or more environment variables.
 *
 * @param envs - a pointer to the linked list of environment variables
 * @param args - an array of keys to unset
 * @return EXIT_OK on success, EXIT_FATAL_ERROR on failure (shouldn't happen)
 */
int	unset_builtin(t_list **envs, const char **args)
{
	int	status;
	int	result;

	if (!envs || !args)
		return (EXIT_FATAL_ERROR);
	status = EXIT_OK;
	while (*args)
	{
		result = remove_env(envs, *args);
		if (result == EXIT_FATAL_ERROR)
			return (EXIT_FATAL_ERROR);
		args++;
	}
	return (status);
}

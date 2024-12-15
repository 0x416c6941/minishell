/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:59:34 by root              #+#    #+#             */
/*   Updated: 2024/12/15 15:41:09 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <stddef.h>
#include <libft.h>

/**
 * Looks for an environment variable with key $identifier in $env
 * 	(which is an $envs from t_vars).
 * Literally a copy paste of ft_find_env(), but with returning
 * 	of a node containing t_env, instead of t_env itself.
 * @param	env			Environment variables.
 * @param	identifier	Key to look for.
 * @return	(Found environment variable) or (NULL), if not found.
 */
static t_list	*ft_find_env_node(t_list *env, const char *key)
{
	while (env != NULL)
	{
		if (ft_strcmp(((t_env *)env->content)->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	unset_builtin(t_minishell_data *data, const char *args[])
{
	size_t	i;
	t_list	*env_node;

	i = 0;
	while (args[i] != NULL)
	{
		env_node = ft_find_env_node(data->vars.envs, args[i]);
		if (env_node != NULL)
			ft_lstremove_node(&data->vars.envs,
				(void (*)(void *))ft_free_t_env, env_node);
		i++;
	}
	return (EXIT_OK);
}

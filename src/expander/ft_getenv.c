/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:55:25 by root              #+#    #+#             */
/*   Updated: 2024/12/03 11:21:00 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <utils.h>
#include <libft.h>
#include <stddef.h>

/**
 * @brief	Looks in a list of $vars for an environment variable named $key.
 * @param	envs	List of environment variables saved as "t_env"s.
 * @param	key		Name of the environment variable to look for.
 * @return	A read-only value of the environment variable if found,
 * 			(NULL) otherwise.
 */
static const char	*ft_get_env_value_by_key(const t_list *envs,
		const char *key)
{
	t_env	*current_node;

	while (envs != NULL)
	{
		current_node = envs->content;
		if (ft_strcmp(current_node->key, key) == 0)
			return (current_node->value);
		envs = envs->next;
	}
	return (NULL);
}

char	*ft_getenv(const t_vars *vars, const char *key)
{
	const char	*value;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(vars->last_exit_status));
	value = ft_get_env_value_by_key(vars->envs, key);
	if (value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

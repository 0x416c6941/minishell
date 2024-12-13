/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:50:32 by root              #+#    #+#             */
/*   Updated: 2024/12/13 16:52:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

char	*get_env_value(t_vars *vars, const char *key)
{
	t_env	*env;
	t_list	*current;

	if (!vars || !key)
		return (NULL);
	current = vars->envs;
	while (current)
	{
		env = (t_env *)current->content;
		if (env && env->key && ft_strcmp(env->key, key) == 0)
			return (env->value);
		current = current->next;
	}
	return (NULL);
}

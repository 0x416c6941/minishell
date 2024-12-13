/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_envs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:01:11 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/13 18:47:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <utils.h>

/**
 * Initialize a single node contaning t_env with environment variable.
 * @warning	Dyamic memory allocation is used.
 * @param	env	Environment variable.
 * @return (If $status is (-1), then malloc() failed and $ret is NULL);
 * 			Otherwise $status is non-negative value, and $ret
 * 				contains a t_env with environment variable.
 */
t_ret	ft_initialize_one_env(const char *env)
{
	t_env	*ret;
	size_t	key_len;

	ret = ft_calloc(1, sizeof(t_env));
	if (ret == NULL)
		return ((t_ret){(-1), NULL});
	key_len = ft_strcspn(env, "=");
	ret->key = (char *)malloc(key_len + 1);
	if (ret->key == NULL)
		return (ft_free_t_env(ret), (t_ret){(-1), NULL});
	(void)ft_strlcpy(ret->key, env, key_len + 1);
	ret->value = ft_strdup(env + key_len + 1);
	if (ret->value == NULL)
		return (ft_free_t_env(ret), (t_ret){(-1), NULL});
	return ((t_ret){0, ret});
}

t_ret	ft_initialize_envs(const char **envp)
{
	t_list	*env_head;
	t_ret	ft_initialize_one_env_status;
	t_list	*env_node;

	env_head = NULL;
	while (*envp != NULL)
	{
		ft_initialize_one_env_status = ft_initialize_one_env(*(envp++));
		if (ft_initialize_one_env_status.status == (-1))
			return (ft_lstclear(&env_head, (void (*)(void *))ft_free_t_env),
				(t_ret){(-1), NULL});
		env_node = ft_lstnew(ft_initialize_one_env_status.ret);
		if (env_node == NULL)
			return (ft_free_t_env(ft_initialize_one_env_status.ret),
				ft_lstclear(&env_head, (void (*)(void *))ft_free_t_env),
				(t_ret){(-1), NULL});
		ft_lstadd_back(&env_head, env_node);
	}
	return ((t_ret){0, env_head});
}

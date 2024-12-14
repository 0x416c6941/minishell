/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_envs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:01:11 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/14 19:54:28 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <utils.h>

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

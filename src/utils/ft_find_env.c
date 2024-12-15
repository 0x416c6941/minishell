/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:54:02 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/15 14:55:48 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <libft.h>
#include <stddef.h>

t_env	*ft_find_env(t_list *env, const char *identifier)
{
	while (env != NULL)
	{
		if (ft_strcmp(((t_env *)env->content)->key, identifier) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

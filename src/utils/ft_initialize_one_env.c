/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_one_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:53:13 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/15 14:13:02 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <stddef.h>
#include <libft.h>
#include <stdlib.h>

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
	if (env[key_len] == '\0')
		ret->value = NULL;
	else
	{
		ret->value = ft_strdup(env + key_len + 1);
		if (ret->value == NULL)
			return (ft_free_t_env(ret), (t_ret){(-1), NULL});
	}
	return ((t_ret){0, ret});
}

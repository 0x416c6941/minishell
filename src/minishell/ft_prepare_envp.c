/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:31:04 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/16 02:18:39 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stddef.h>
#include <libft.h>
#include <stdlib.h>
#include <utils.h>

size_t	ft_cnt_envs(t_minishell_data *data)
{
	size_t	cnt;
	t_list	*env;

	cnt = 0;
	env = data->vars.envs;
	while (env != NULL)
	{
		if (((t_env *)env->content)->value != NULL)
			cnt++;
		env = env->next;
	}
	return (cnt);
}

char	*ft_prepare_env(const t_env *env)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(env->key) + ft_strlen(env->value) + 1;
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	ret[ft_strlcpy(ret, env->key, ft_strlen(env->key) + 1)] = '=';
	(void)ft_strlcpy(ret + ft_strlen(env->key) + 1,
		env->value, ft_strlen(env->value) + 1);
	return (ret);
}

char	**ft_prepare_envp(t_minishell_data *data)
{
	size_t	envs_cnt;
	char	**ret;
	size_t	i;
	t_env	*env;
	char	*to_append;

	envs_cnt = ft_cnt_envs(data);
	ret = (char **)ft_calloc(envs_cnt + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < envs_cnt)
	{
		env = ft_lstat(data->vars.envs, i)->content;
		if (env->value != NULL)
		{
			to_append = ft_prepare_env(env);
			if (to_append == NULL)
				return (ft_split_free(ret), NULL);
			ret[i] = to_append;
		}
		i++;
	}
	return (ret[i] = NULL, ret);
}

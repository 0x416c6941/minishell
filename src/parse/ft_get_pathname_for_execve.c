/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pathname_for_execve.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:49:21 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/30 01:29:07 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <libft.h>

t_ret	ft_get_pathname_for_execve(const char *arg)
{
	t_ret	ret;
	char	**path_env_split;

	ret.ret = NULL;
	if (*arg == '/' || *arg == '.')
	{
		ret.status = ft_check_pathname(arg);
		if (ret.status == PATHNAME_OK)
		{
			ret.ret = ft_strdup(arg);
			if (ret.ret == NULL)
				return ((t_ret){(-1), NULL});
		}
		return (ret);
	}
	path_env_split = ft_split(getenv("PATH"), ':');
	if (path_env_split == NULL)
		return ((t_ret){(-1), NULL});
	ret = ft_get_pathname_for_execve_from_path_env(arg,
			(const char **)path_env_split);
	ft_split_free(path_env_split);
	return (ret);
}

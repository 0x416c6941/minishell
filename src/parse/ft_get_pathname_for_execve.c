/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pathname_for_execve.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:49:21 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/01 00:55:35 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

t_ret	ft_get_pathname_for_execve(const char *arg)
{
	t_ret	ret;

	if (ft_is_builtin(arg))
	{
		ret.ret = ft_strdup(arg);
		if (ret.ret == NULL)
			return ((t_ret){(-1), NULL});
		return (ret.status = PATHNAME_IS_BUILTIN, ret);
	}
	else if (*arg == '/' || *arg == '.')
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
	return (ft_get_pathname_for_execve_from_path_env(arg));
}

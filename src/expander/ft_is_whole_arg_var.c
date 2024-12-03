/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_whole_arg_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:51:45 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/03 16:00:39 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <parse.h>
#include <libft.h>
#include <stdlib.h>

int	ft_is_whole_arg_var(const char *arg)
{
	t_ret	status;

	while (*arg != '\0')
	{
		if (*arg == '$')
		{
			status = ft_extract_var_name(arg);
			if (status.status == -1)
				return (-1);
			else if (status.status == 0)
				return (free(status.ret), 0);
			arg += ft_strlen(status.ret) + 1;
			free(status.ret);
			continue ;
		}
		return (0);
	}
	return (1);
}

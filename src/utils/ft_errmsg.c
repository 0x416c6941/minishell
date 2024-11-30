/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errmsg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:04:47 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/01 00:07:12 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <stdlib.h>
#include <libft.h>

int	ft_errmsg(const char *msg)
{
	if (write(STDERR_FILENO, MINISHELL_PREFIX,
			ft_strlen(MINISHELL_PREFIX)) == -1
		|| write(STDERR_FILENO, msg, ft_strlen(msg)) == -1)
		return (-1);
	return (0);
}

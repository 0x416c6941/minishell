/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_emptiness_raw.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:16:45 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/03 18:17:23 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>

int	ft_check_emptiness_raw(const t_exec *raw_cmd)
{
	if (raw_cmd->args == NULL
		&& raw_cmd->stdin_redirs == NULL && raw_cmd->stdout_redirs == NULL)
		return (-1);
	return (0);
}

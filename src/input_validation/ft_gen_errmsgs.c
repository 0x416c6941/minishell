/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gen_errmsgs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:54:55 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/10 12:10:49 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <libft.h>
#include <stddef.h>
#include <utils.h>
#include <parse.h>

int	ft_gen_errmsgs(const t_list *parsed_cmd)
{
	const t_ret	*cmd_status;

	while (parsed_cmd != NULL)
	{
		cmd_status = parsed_cmd->content;
		if (cmd_status->status != PATHNAME_IS_BUILTIN
			&& cmd_status->status != CMD_OK)
			if (ft_gen_errmsg(cmd_status->status, parsed_cmd->next) == -1)
				return (-1);
		parsed_cmd = parsed_cmd->next;
	}
	return (0);
}

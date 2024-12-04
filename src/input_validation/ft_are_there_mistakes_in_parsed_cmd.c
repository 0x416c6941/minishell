/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_are_there_mistakes_in_parsed_cmd.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:43:56 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/04 19:29:54 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <utils.h>
#include <stddef.h>
#include <parse.h>

int	ft_are_there_mistakes_in_parsed_cmd(const t_list *parsed_cmd)
{
	const t_ret	*cmd_status;

	while (parsed_cmd != NULL)
	{
		cmd_status = parsed_cmd->content;
		if (cmd_status->status != PATHNAME_IS_BUILTIN
			&& cmd_status->status != CMD_OK)
			return (1);
		parsed_cmd = parsed_cmd->next;
	}
	return (0);
}

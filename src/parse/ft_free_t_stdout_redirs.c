/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_t_stdout_redirs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:53:09 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 14:20:18 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <stdlib.h>

void	ft_free_t_stdout_redirs(t_stdout_redir **stdout_redir)
{
	t_stdout_redir	*next;

	while (*stdout_redir != NULL)
	{
		free((char *)((*stdout_redir)->output_file));
		next = (*stdout_redir)->next;
		free(*stdout_redir);
		*stdout_redir = next;
	}
}

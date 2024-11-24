/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_t_stdin_redirs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:53:09 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 14:19:47 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <stdlib.h>

void	ft_free_t_stdin_redirs(t_stdin_redir **stdin_redir)
{
	t_stdin_redir	*next;

	while (*stdin_redir != NULL)
	{
		if ((*stdin_redir)->redir_type == file)
			free((char *)((*stdin_redir)->redir_data.stdin_file));
		else if ((*stdin_redir)->redir_type == heredoc)
			free((char *)((*stdin_redir)->redir_data.heredoc_eof));
		next = (*stdin_redir)->next;
		free(*stdin_redir);
		*stdin_redir = next;
	}
}

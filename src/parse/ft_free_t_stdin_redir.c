/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_t_stdin_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:53:09 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 17:55:25 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <stdlib.h>

void	ft_free_t_stdin_redir(t_stdin_redir *stdin_redir)
{
	if (stdin_redir->redir_type == file)
		free((char *)(stdin_redir->redir_data.stdin_file));
	else if (stdin_redir->redir_type == heredoc)
		free((char *)(stdin_redir->redir_data.heredoc_eof));
	free(stdin_redir);
}

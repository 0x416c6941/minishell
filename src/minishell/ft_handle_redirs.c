/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:37:58 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/15 01:28:35 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <expander.h>

/**
 * 25 lines of code per function in such a project is ridiculous and absurd.
 * @param	stdin_redir	The redirection to be handled.
 * @return	(-1), if something went wrong;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_handle_stdin_redir(t_stdin_redir *stdin_redir)
{
	int	fd;

	if (stdin_redir->redir_type == file)
	{
		fd = open(stdin_redir->data, O_RDONLY);
		if (fd == -1)
			return (-1);
	}
	else
	{
		fd = ft_handle_heredoc(stdin_redir->data);
		if (fd == -1)
			return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return ((void)close(fd), -1);
	else if (close(fd) == -1)
		return (-1);
	return (0);
}

/**
 * 25 lines of code per function in such a project is ridiculous and absurd.
 * @param	stdout_redir	The redirection to be handled.
 * @return	(-1), if something went wrong;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_handle_stdout_redir(t_stdout_redir *stdout_redir)
{
	int	fd;

	if (stdout_redir->redir_type == overwrite)
	{
		fd = open(stdout_redir->output_file,
				O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC, 0644);
		if (fd == -1)
			return (-1);
	}
	else
	{
		fd = open(stdout_redir->output_file,
				O_CREAT | O_WRONLY | O_APPEND | O_CLOEXEC, 0644);
		if (fd == -1)
			return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return ((void)close(fd), -1);
	else if (close(fd) == -1)
		return (-1);
	return (0);
}

int	ft_handle_redirs(t_exec *cmd)
{
	t_list	*redir;

	redir = cmd->stdin_redirs;
	while (redir != NULL)
	{
		if (ft_handle_stdin_redir((t_stdin_redir *)redir->content) == -1)
			return (-1);
		redir = redir->next;
	}
	redir = cmd->stdout_redirs;
	while (redir != NULL)
	{
		if (ft_handle_stdout_redir((t_stdout_redir *)redir->content) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

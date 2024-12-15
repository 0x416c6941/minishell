/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_stdin_stdout.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:02:22 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/15 01:22:44 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

int	ft_restore_stdin_stdout(t_minishell_data *data)
{
	if (dup2(data->real_stdin_fd, STDIN_FILENO) == -1
		|| dup2(data->real_stdout_fd, STDOUT_FILENO) == -1)
		return (MESSED_UP);
	return (0);
}

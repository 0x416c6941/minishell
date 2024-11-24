/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_t_stdout_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:53:09 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 17:55:39 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stddef.h>
#include <stdlib.h>

void	ft_free_t_stdout_redir(t_stdout_redir *stdout_redir)
{
	free((char *)(stdout_redir->output_file));
	free(stdout_redir);
}

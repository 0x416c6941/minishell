/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc_delim.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:47:01 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/04 18:50:56 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <libft.h>

void	ft_expand_heredoc_delim(char *heredoc_delim)
{
	while (*heredoc_delim != '\0')
	{
		if (*heredoc_delim == '\'' || *heredoc_delim == '\"')
		{
			(void)ft_memmove(heredoc_delim, heredoc_delim + 1,
				ft_strlen(heredoc_delim));
			continue ;
		}
		heredoc_delim++;
	}
}

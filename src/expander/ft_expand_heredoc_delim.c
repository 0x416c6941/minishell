/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc_delim.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:47:01 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/10 11:46:06 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <utils.h>
#include <parse.h>
#include <libft.h>

void	ft_expand_heredoc_delim(char *heredoc_delim)
{
	enum e_quotes_type	quotes_type;
	enum e_quotes_type	new_quotes_type;

	quotes_type = no_quotes;
	while (*heredoc_delim != '\0')
	{
		if (*heredoc_delim == '\'' || *heredoc_delim == '\"')
		{
			new_quotes_type = quotes_type;
			ft_handle_quotes(*heredoc_delim, &new_quotes_type);
			if (new_quotes_type != quotes_type)
				(void)ft_memmove(heredoc_delim, heredoc_delim + 1,
					ft_strlen(heredoc_delim));
			else
				heredoc_delim++;
			quotes_type = new_quotes_type;
		}
		else
			heredoc_delim++;
	}
}

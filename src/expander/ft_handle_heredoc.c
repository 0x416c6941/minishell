/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:51:23 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/15 20:52:09 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stddef.h>
#include <utils.h>
#include <stdlib.h>

int	ft_handle_heredoc(const char *eof_str)
{
	int		ret[2];
	char	*input;

	if (pipe(ret) == -1)
		return (-1);
	while (42)
	{
		input = readline("heredoc> ");
		if (input == NULL)
		{
			if (close(ret[1]) == -1 || ft_errmsg("heredoc: caught EOF\n") == -1)
				return ((void)close(ret[0]), -1);
			return (ret[0]);
		}
		else if (ft_strcmp(input, eof_str) == 0)
		{
			if (close(ret[1]) == -1)
				return ((void)close(ret[0]), free(input), -1);
			return (free(input), ret[0]);
		}
		if (write(ret[1], input, ft_strlen(input)) == -1
			|| write(ret[1], "\n", 1) == -1)
			return ((void)close(ret[0]), (void)close(ret[1]), free(input), -1);
		free(input);
	}
}

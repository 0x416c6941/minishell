/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:51:23 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/10 13:05:32 by asagymba         ###   ########.fr       */
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
			if (close(ret[1]) == -1)
				return ((void)close(ret[0]),
					(void)ft_errmsg("close()-san fa1led ;("), -1);
			else if (ft_errmsg("heredoc: caught EOF") == -1)
				return ((void)close(ret[0]), -1);
			return (ret[0]);
		}
		else if (ft_strcmp(input, eof_str) == 0)
			return (free(input), ret[0]);
		if (write(ret[1], input, ft_strlen(input)) == -1
			|| write(ret[1], "\n", 1) == -1)
			return ((void)close(ret[0]), (void)close(ret[1]),
				(void)ft_errmsg("write()-san fa1led x_x"), free(input), -1);
		free(input);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:26:25 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 13:17:42 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include <parse.h>
#include <stddef.h>

#define REQUIRED_ARGC	2
#define USAGE_MSG		"Usage: ./a.out $ARG\n"
#define INVALID_ARGS	1

int	main(int argc, char **argv)
{
	char	*next_token;
	char	*last_token;
	char	*next_arg;
	char	*last_arg;

	if (argc != REQUIRED_ARGC)
	{
		(void)write(STDERR_FILENO, USAGE_MSG, sizeof(USAGE_MSG));
		return (INVALID_ARGS);
	}
	(void)ft_printf("Hello!\n");
	(void)ft_printf("Testing parser...\n");
	(void)ft_printf("\n");
	next_token = ft_get_next_token(*(++argv), &last_token);
	while (next_token != NULL)
	{
		next_arg = ft_get_next_arg(next_token, &last_arg);
		while (next_arg != NULL)
		{
			ft_printf("%s\n", next_arg);
			if (ft_check_arg_quotes(next_arg) == -1)
				ft_printf("\tSomething gone wrong :p\n");
			next_arg = ft_get_next_arg(NULL, &last_arg);
		}
		next_token = ft_get_next_token(NULL, &last_token);
	}
	return (0);
}

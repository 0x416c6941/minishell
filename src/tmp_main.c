/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:26:25 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 12:14:02 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include <parse_utils.h>
#include <stddef.h>

#define REQUIRED_ARGC	2
#define USAGE_MSG		"Usage: ./a.out $ARG\n"
#define INVALID_ARGS	1

int	main(int argc, char **argv)
{
	char	*next_token;
	char	*last;

	if (argc != REQUIRED_ARGC)
	{
		(void)write(STDERR_FILENO, USAGE_MSG, sizeof(USAGE_MSG));
		return (INVALID_ARGS);
	}
	(void)ft_printf("Hello!\n");
	(void)ft_printf("Testing parser...\n");
	(void)ft_printf("\n");
	next_token = ft_get_next_token(*(++argv), &last);
	while (next_token != NULL)
	{
		ft_printf("%s\n", next_token);
		next_token = ft_get_next_token(NULL, &last);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:26:25 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 20:07:35 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include <parse.h>
#include <stddef.h>

#define REQUIRED_ARGC	2
#define USAGE_MSG		"Usage: ./a.out $ARG\n"
#define INVALID_ARGS	1

#define BAD_MSG		"Something went really wrong.\n"
#define MESSED_UP	2

int	main(int argc, char **argv)
{
	char	*token;
	char	*next_token;
	t_ret	status;
	t_exec	*cmd;

	if (argc != REQUIRED_ARGC)
	{
		(void)write(STDERR_FILENO, USAGE_MSG, sizeof(USAGE_MSG));
		return (INVALID_ARGS);
	}
	(void)ft_printf("Hello!\n");
	(void)ft_printf("Testing parser...\n");
	(void)ft_printf("\n");
	token = ft_get_next_token(*(++argv), &next_token);
	while (token != NULL)
	{
		status = ft_get_cmd_raw_quotes(token);
		if (status.status == -1)
		{
			(void)write(STDERR_FILENO, BAD_MSG, sizeof(BAD_MSG));
			return (MESSED_UP);
		}
		cmd = status.ret;
		ft_free_t_exec(cmd);
		token = ft_get_next_token(NULL, &next_token);
	}
	return (0);
}

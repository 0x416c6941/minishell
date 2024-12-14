/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:02:44 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/14 23:45:38 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <utils.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell_data	data;
	bool				should_have_left;
	int					exit_code;

	(void)argc;
	(void)argv;
	if (ft_init_data((const char **)envp, &data) == -1)
		return (ft_free_data(&data), ft_errmsg("ft_init_data() failed.\n"), 1);
	minishell(&data);
	should_have_left = data.should_leave;
	exit_code = data.with_which_code;
	if (ft_free_data(&data) == -1)
		return (MESSED_UP);
	if (!should_have_left)
		if (ft_errmsg("data.should_leave is false, but left anyway\n")
			== -1)
			return (MESSED_UP);
	return (exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:02:44 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/14 21:09:34 by asagymba         ###   ########.fr       */
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
		return (ft_errmsg("ft_init_data() failed.\n"), 1);
	minishell(&data);
	should_have_left = data.should_leave;
	exit_code = data.with_which_code;
	ft_free_data(&data);
	if (!should_have_left)
		(void)ft_errmsg("data.should_leave is false, but leaving anyway.\n");
	return (exit_code);
}

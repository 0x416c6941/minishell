/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:02:44 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/14 20:28:06 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell_data	data;

	(void)argc;
	(void)argv;
	if (ft_init_data((const char **)envp, &data) == -1)
		return (ft_errmsg("ft_init_data() failed."), 1);
	ft_free_data(&data);
}

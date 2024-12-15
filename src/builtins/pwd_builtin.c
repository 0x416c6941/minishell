/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:17:38 by root              #+#    #+#             */
/*   Updated: 2024/12/15 15:50:42 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <linux/limits.h>
#include <unistd.h>
#include <utils.h>
#include <stdbool.h>

int	pwd_builtin(t_minishell_data *data, const char *args[])
{
	char	buf[PATH_MAX + 1];

	(void)args;
	if (getcwd(buf, PATH_MAX) == NULL)
	{
		if (ft_errmsg("pwd: getcwd() failed\n") == -1)
		{
			data->should_leave = true;
			data->with_which_code = MESSED_UP;
		}
		return (EXIT_ERROR);
	}
	if (write(STDOUT_FILENO, buf, PATH_MAX) == -1
		|| write(STDOUT_FILENO, "\n", 1) == -1)
		return (data->should_leave = true,
			data->with_which_code = MESSED_UP, EXIT_ERROR);
	return (EXIT_OK);
}

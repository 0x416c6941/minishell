/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:17:38 by root              #+#    #+#             */
/*   Updated: 2024/12/13 17:04:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#define PATH_MAX 4096

int	pwd_builtin(t_vars *vars, const char **args)
{
	char	buf[PATH_MAX];
	char	*pwd;

	(void)args;
	pwd = get_env_value(vars, "PWD");
	if (!pwd)
	{
		pwd = getcwd(buf, PATH_MAX);
		if (!pwd)
		{
			ft_errmsg("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			return (EXIT_FATAL_ERROR);
		}
	}
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	return (EXIT_OK);
}

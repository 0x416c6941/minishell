/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:17:38 by root              #+#    #+#             */
/*   Updated: 2024/12/13 20:04:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#define PATH_MAX 4096
#define PWD_ERR "minishell: pwd: error retrieving current directory: "
#define GETCWD_ERR "getcwd: cannot access parent directories: "
#define NO_DIR_ERR "No such file or directory\n"

int	pwd_builtin(t_vars *vars, const char **args)
{
	char	buf[PATH_MAX];
	char	*cwd;

	(void)vars;
	(void)args;
	cwd = getcwd(buf, sizeof(buf));
	if (!cwd)
	{
		if (write(STDERR_FILENO, PWD_ERR, ft_strlen(PWD_ERR)) == -1
			|| write(STDERR_FILENO, GETCWD_ERR, ft_strlen(GETCWD_ERR)) == -1
			|| write(STDERR_FILENO, NO_DIR_ERR, ft_strlen(NO_DIR_ERR)) == -1)
			return (EXIT_FATAL_ERROR);
	}
	if (write(STDOUT_FILENO, cwd, ft_strlen(cwd)) == -1 || write(STDOUT_FILENO,
			"\n", 1) == -1)
		return (EXIT_FATAL_ERROR);
	return (EXIT_OK);
}

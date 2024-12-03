/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pathname_for_execve.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:49:21 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/03 18:23:48 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <expander.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Returns the string made by the pattern: $path + '/' + $arg.
 * '/' is added only if path doesn't contain a trailing slash already.
 * @brief	Norminette bypass.
 * @warning	Dynamic memory allocation is used.
 * @param	path	A path to the directory, possibly containing cmd.
 * @param	arg		A command to append to the end of path.
 */
static char	*ft_get_pathname_for_execve_find_first_in_path_append_arg(
		const char *path, const char *arg)
{
	char	*path_with_slash;
	char	*exec_path;

	path_with_slash = ft_strrchr(path, '/');
	if (path_with_slash != NULL && *(path_with_slash + 1) == '\0')
		path_with_slash = ft_strdup(path);
	else
		path_with_slash = ft_strjoin(path, "/");
	if (path_with_slash == NULL)
		return (NULL);
	exec_path = ft_strjoin(path_with_slash, arg);
	free(path_with_slash);
	return (exec_path);
}

/**
 * Tries to find the first executable in directory
 * 	*$path_env_split + '/' + arg.
 * If no such an executable is found, NULL is returned.
 * @brief	Norminette bypass.
 * @param	arg				A file to try for (F_OK | W_OK)
 * 							in $path_env_split array.
 * @param	path_env_split	Result of ft_split() on $PATH variable.
 * @return	If $status == (-1), then malloc() failed and $ret is NULL;
 * 			if $status == (EXEC_ISNT_IN_PATH),
 * 				then command wasn't found and $ret is NULL;
 * 			otherwise, $status == (CMD_OK),
 * 				and $ret is a path to the first found executable.
 */
t_ret	ft_get_pathname_for_execve_find_first_in_path(
		const char **path_env_split, const char *arg)
{
	size_t	i;
	char	*exec_path;

	i = 0;
	while (path_env_split[i] != NULL)
	{
		exec_path
			= ft_get_pathname_for_execve_find_first_in_path_append_arg(
				path_env_split[i], arg);
		if (exec_path == NULL)
			return ((t_ret){(-1), NULL});
		else if (access(exec_path, F_OK | X_OK) == 0)
			return ((t_ret){CMD_OK, exec_path});
		free(exec_path);
		i++;
	}
	return ((t_ret){EXEC_ISNT_IN_PATH, NULL});
}

/**
 * Wrapper for ft_get_pathname_for_execve_find_first_in_path(),
 * which takes care of getting "PATH" variable and splitting into directories.
 * @brief	Norminette bypass.
 * @param	vars	Pointer to structure containing last exit status
 * 					and environment variables in a key-pair structure.
 * @param	arg		Argument to be expanded.
 * @return	If $status == (CMD_OK), then $ret will contain an executable file;
 * 			otherwise $status will reflect it's error code,
 * 				and $ret will be (NULL).
 */
static t_ret	ft_get_pathname_for_execve_from_path_env(const t_vars *vars,
		const char *arg)
{
	char	*path_env;
	char	**path_env_split;
	t_ret	ret;

	path_env = ft_get_env_value(vars, "PATH");
	if (path_env == NULL)
		return ((t_ret){(-1), NULL});
	path_env_split = ft_split(path_env, ':');
	if (path_env_split == NULL)
		return (free(path_env), (t_ret){(-1), NULL});
	free(path_env);
	ret = ft_get_pathname_for_execve_find_first_in_path(
			(const char **)path_env_split, arg);
	ft_split_free(path_env_split);
	return (ret);
}

t_ret	ft_get_pathname_for_execve(const t_vars *vars, const char *arg)
{
	t_ret	ret;

	ret.ret = NULL;
	if (arg == NULL)
		return ((t_ret){CMD_OK, NULL});
	else if (ft_is_builtin(arg))
	{
		ret.ret = ft_strdup(arg);
		if (ret.ret == NULL)
			return ((t_ret){(-1), NULL});
		return (ret.status = PATHNAME_IS_BUILTIN, ret);
	}
	else if (*arg == '/' || *arg == '.')
	{
		ret.status = ft_check_pathname(arg);
		if (ret.status == CMD_OK)
		{
			ret.ret = ft_strdup(arg);
			if (ret.ret == NULL)
				return ((t_ret){(-1), NULL});
		}
		return (ret);
	}
	return (ft_get_pathname_for_execve_from_path_env(vars, arg));
}

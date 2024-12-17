/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:18:41 by root              #+#    #+#             */
/*   Updated: 2024/12/17 13:30:12 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <linux/limits.h>
#include <stddef.h>
#include <utils.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * ... Norminette.
 * @param	data	Minishell's data.
 * @param	env		$env2 from ft_add_or_modify_env().
 * @return	Same as cd_builtin().
 */
static int	ft_add_or_modify_env_final_part(t_minishell_data *data, char *env)
{
	t_ret	status;
	t_list	*to_append;

	status = ft_initialize_one_env(env);
	if (status.status == -1)
		return (free(env), data->should_leave = true,
			data->with_which_code = MESSED_UP, EXIT_ERROR);
	free(env);
	to_append = ft_lstnew(status.ret);
	if (to_append == NULL)
		return (ft_free_t_env(status.ret), data->should_leave = true,
			data->with_which_code = MESSED_UP, EXIT_ERROR);
	ft_lstadd_back(&data->vars.envs, to_append);
	return (0);
}

/**
 * Adds or modifies an environment variable, contained in $arg
 * (with identifier $identifier) to / in $data.
 * Almost a copy paste of ft_add_or_modify_env() from export_builtin.c.
 * @param	data		Minishell's data.
 * @param	key			Key of the argument.
 * @param	new_value	New value of the argument.
 * @param	arg			Argument to add or modify.
 * @return	Same as cd_builtin().
 */
static int	ft_add_or_modify_env(t_minishell_data *data, const char *key,
		const char *new_value)
{
	t_env	*saved;
	char	*env1;
	char	*env2;

	saved = ft_find_env(data->vars.envs, key);
	if (saved != NULL)
	{
		free(saved->value);
		saved->value = ft_strdup(new_value);
		if (saved->value == NULL)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, EXIT_ERROR);
		return (EXIT_OK);
	}
	env1 = ft_strjoin(key, "=");
	if (env1 == NULL)
		return (data->should_leave = true,
			data->with_which_code = MESSED_UP, EXIT_ERROR);
	env2 = ft_strjoin(env1, new_value);
	if (env2 == NULL)
		return (free(env1), data->should_leave = true,
			data->with_which_code = MESSED_UP, EXIT_ERROR);
	free(env1);
	return (ft_add_or_modify_env_final_part(data, env2));
}

/**
 * Yep, you guessed it, - yet another Norminette bypass!
 * @param	data	Minishell's data.
 * @param	oldpwd	Old working directory.
 * $param	newpwd	New working directory.
 * @return	Same as cd_builtin().
 */
static int	cd_builtin_second_continuation(t_minishell_data *data,
		const char *oldpwd, const char *to_chdir)
{
	char	newpwd[PATH_MAX + 1];

	if (chdir(to_chdir) == -1)
	{
		if (ft_errmsg("cd: chdir() failed\n") == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, EXIT_ERROR);
		return (EXIT_ERROR);
	}
	if (getcwd(newpwd, PATH_MAX) == NULL)
	{
		(void)ft_errmsg("cd: getcwd() after chdir() failed\n");
		data->should_leave = true;
		data->with_which_code = MESSED_UP;
		return (EXIT_ERROR);
	}
	if (ft_add_or_modify_env(data, "OLDPWD", oldpwd) == -1
		|| ft_add_or_modify_env(data, "PWD", newpwd) == -1)
		return (data->should_leave = true,
			data->with_which_code = MESSED_UP, EXIT_ERROR);
	return (EXIT_OK);
}

/**
 * Another Norminette bypass.
 * Actually, line 15 isn't good, but... I don't care at this point.
 * @param	data	Minishell's data.
 * @param	args	$args passed to the cd_builtin().
 * @param	oldpwd	Old working directory.
 * @return	Same as cd_builtin().
 */
static int	cd_builtin_first_continuation(t_minishell_data *data,
		const char *args[], const char *oldpwd)
{
	char	*home;

	if (*args == NULL)
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			if (ft_errmsg("cd: HOME not set\n") == -1)
				return (data->should_leave = true,
					data->with_which_code = MESSED_UP, EXIT_ERROR);
			return (EXIT_ERROR);
		}
		return (cd_builtin_second_continuation(data, oldpwd, home));
	}
	if (ft_strlen(*args) > PATH_MAX)
	{
		if (ft_errmsg("cd: Path too long\n") == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, EXIT_ERROR);
		return (EXIT_ERROR);
	}
	return (cd_builtin_second_continuation(data, oldpwd, *args));
}

int	cd_builtin(t_minishell_data *data, const char *args[])
{
	char	oldpwd[PATH_MAX + 1];

	if (args[0] != NULL && args[1] != NULL)
	{
		if (ft_errmsg("cd: Too many arguments\n") == -1)
		{
			data->should_leave = true;
			data->with_which_code = MESSED_UP;
		}
		return (EXIT_ERROR);
	}
	else if (getcwd(oldpwd, PATH_MAX) == NULL)
	{
		if (ft_errmsg("cd: getcwd() failed\n") == -1)
		{
			data->should_leave = true;
			data->with_which_code = MESSED_UP;
		}
		return (EXIT_ERROR);
	}
	return (cd_builtin_first_continuation(data, args, oldpwd));
}

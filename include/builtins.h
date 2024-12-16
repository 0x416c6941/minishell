/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:24:29 by root              #+#    #+#             */
/*   Updated: 2024/12/16 16:18:48 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <minishell.h>
# include <utils.h>

/**
 * ---------------------------------------------------------------------------
 * Constants.
 * ---------------------------------------------------------------------------
 */
/**
 * In case of builtins, we'll save their exit code,
 * which should always be in the same pattern: 0 for success,
 * 	GENERALLY 1 for error.
 * 		This can be potentially furtherly adjusted,
 * 		please refer to individual builtin documentation.
 */
# define EXIT_OK	0
# define EXIT_ERROR	1

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * Please refer to `$ man 1 echo`.
 * Only "-n" flag is implemented.
 * @param	args	Array of arguments passed to the "echo" command,
 *					excluding the command itself.
*						(Please refer to args_for_execve)
 * @return	EXIT_OK on success;
 * 			EXIT_ERROR on failure (ideally should never happen: write fail);
 * 				data->should_leave will be set to true in this case,
 * 				and data->with_which_code will bet to MESSED_UP.
 */
int	echo_builtin(t_minishell_data *data, const char *args[]);

/**
 * Changes working directory. No options are supported.
 * @param	data	Minishell's data.
 * @param	args	Array of arguments passed to the "cd" command,
 * 					excluding the command itself.
*						(Please refer to args_for_execve)
 * @return	EXIT_OK on success;
 * 			EXIT_ERROR on failure:
 * 				If write() failed,
 * 					data->should_leave will be set to true,
 * 					and data->with_which_code will bet to MESSED_UP.
 * 				Otherwise it just means that user has entered
 * 				either non-existing directory, or the one they don't have
 * 					access to.
 * 				Both however should be fine.
 */
int	cd_builtin(t_minishell_data *data, const char *args[]);

/**
 * Writes the current working directory to the standard output.
 * @param	data	Minishell's data.
 * @param	args	Array of arguments passed to the "pwd" command,
 *					excluding the command itself.
 * 						(Please refer to args_for_execve)
 * @return	EXIT_OK on success;
 * 			EXIT_ERROR on failure (ideally should never happen: write fail);
 * 				data->should_leave will be set to true in this case,
 * 				and data->with_which_code will bet to MESSED_UP.
 */
int	pwd_builtin(t_minishell_data *data, const char *args[]);

/**
 * Norminette bypass for export_builtin().
 * @param	data	Minishell's data.
 * @param	arg		Argument to check and, if everything is correct,
 * 					add to data->vars.envs.
 * @return	-1, if something went wrong and we should leave;
 * 			0, if identifier was incorrect;
 * 			Some positive value otherwise.
 */
int	export_builtin_continuation(t_minishell_data *data, const char *arg);

/**
 * Exports all variables in $args. If argument contains a '=',
 * 	then it also be seen as an environment variable.
 * 	It will otherwise be seen only in `$ export` as "declare -x".
 * If $args is empty, it will print all saved variables.
 * @param	data	Minishell's data.
 * @param	args	Array of arguments passed to the "export" command,
 * 					excluding the command itself.
 *						(Please refer to args_for_execve)
 * @return	EXIT_OK on success;
 * 			EXIT_ERROR on failure (ideally should never happen: write fail);
 * 				data->should_leave will be set to true in this case,
 * 				and data->with_which_code will bet to MESSED_UP.
 */
int	export_builtin(t_minishell_data *data, const char *args[]);

/**
 * Unsets one or more environment variables.
 * @param	data	Minishell's data.
 * @param	args	Array of arguments passed to the "unset" command,
 * 					excluding the command itself.
 *						(Please refer to args_for_execve)
 * @return	EXIT_OK on success;
 * 			EXIT_ERROR on failure (ideally should never happen: write fail);
 * 				data->should_leave will be set to true in this case,
 * 				and data->with_which_code will bet to MESSED_UP.
 */
int	unset_builtin(t_minishell_data *data, const char *args[]);

/**
 * Prints the environment variables stored in the t_vars structure.
 * Please note that this is a stripped-down version:
 * 	real `$ env` command allows you to run a program
 * 	in the modified environment, this version only prints
 * 	the currently held environment variables.
 * @param	data	Minishell data.
 * @param	args	Array of arguments passed to the "env" command,
 * 					excluding the command itself.
 *						(Please refer to args_for_execve)
 * @return	EXIT_OK on success;
 * 			EXIT_ERROR on failure:
 * 				either if $args contain some arguments,
 * 				or if write() failed
 * 					(data->should_leave will be true in this case,
 * 					and data->with_which_code will be set to MESSED_UP).
 */
int	env_builtin(t_minishell_data *data, const char *args[]);

/**
 * Exits the shell. For more details, please see `$ man 1p exit`.
 * @param	data	Minishell's data.
 * @param	args	Array of arguments passed to the "exit" command,
 * 					excluding the command itself.
 *						(Please refer to args_for_execve)
 * @return	EXIT_ERROR, if got more than one argument or write() failed:
 * 				data->should_leave will be edited only in case
 * 				of write() failure,
 * 				and data->with_which_code will be set to MESSED_UP;
 * 			EXIT_OK otherwise:
 * 				data->should_leave will be set to true in this case,
 * 				and data->with_which_code will be set to an exit code
 * 					to leave the shell with.
 */
int	exit_builtin(t_minishell_data *data, const char *args[]);

#endif /* BUILTINS_H */

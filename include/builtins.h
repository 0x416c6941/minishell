/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:24:29 by root              #+#    #+#             */
/*   Updated: 2024/12/15 14:03:24 by asagymba         ###   ########.fr       */
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
int			echo_builtin(t_minishell_data *data, const char *args[]);

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
int			export_builtin(t_minishell_data *data, const char *args[]);

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
int			env_builtin(t_minishell_data *data, const char *args[]);

int			exit_builtin(const char *args[], int *last_exit_code);
const char	*parse_sign_and_skip_whitespace(const char *nptr, int *sign);
int			pwd_builtin(t_vars *vars, const char **args);
int			unset_builtin(t_list **envs, const char **args);

#endif /* BUILTINS_H */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:24:05 by root              #+#    #+#             */
/*   Updated: 2024/12/13 15:15:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

/**
 * @brief Checks for the "-n" flag in the provided arguments.
 *
 * Iterates through the arguments to check if the "-n" flag is present.
 * If found, it sets the `newline` parameter to `false`
 * and skips those arguments. Otherwise, it leaves `newline` as `true`.
 *
 * @param args Pointer to the array of arguments.
 * @param newline Pointer to a boolean indicating whether a newline
 * should be printed.
 * @return const char** Pointer to the remaining arguments after
 * processing "-n" flags.
 */
static const char	**check_flag(const char **args, bool *newline)
{
	*newline = true;
	while (*args && ft_strcmp(*args, "-n") == 0)
	{
		*newline = false;
		args++;
	}
	return (args);
}

/**
 * @brief Executes the built-in "echo" command.
 *  	- If the "-n" flag is not present, it appends a newline at the end.
 * @param args Array of arguments passed to the "echo" command,
 * excluding the command itself. (args_for_execve)
 * @return int Returns EXIT_OK (0) on success or EXIT_FATAL_ERROR (1)
 * on failure (write fail if possible) or if `args` is NULL (just in case)
 */
int	echo_builtin(const char *args[])
{
	bool	newline;

	if (!args)
		return (EXIT_FATAL_ERROR);
	args = check_flag(args, &newline);
	while (*args != NULL)
	{
		if (write(1, *args, ft_strlen(*args)) == -1)
			return (EXIT_FATAL_ERROR);
		if (*(args + 1) != NULL)
		{
			if (write(1, " ", 1) == -1)
				return (EXIT_FATAL_ERROR);
		}
		args++;
	}
	if (newline)
	{
		if (write(1, "\n", 1) == -1)
			return (EXIT_FATAL_ERROR);
	}
	return (EXIT_OK);
}

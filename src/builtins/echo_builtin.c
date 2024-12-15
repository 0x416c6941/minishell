/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:24:05 by root              #+#    #+#             */
/*   Updated: 2024/12/15 01:26:41 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <stdbool.h>
#include <stddef.h>
#include <libft.h>
#include <unistd.h>

/**
 * Checks for the "-n" flag in the provided arguments.
 * Iterates through the arguments to check if the "-n" flag is present.
 * If found, it sets the `newline` parameter to `false`
 * and skips those arguments. Otherwise, it leaves `newline` as `true`.
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

int	echo_builtin(t_minishell_data *data, const char *args[])
{
	bool	newline;

	if (args == NULL)
		return (EXIT_OK);
	args = check_flag(args, &newline);
	while (*args != NULL)
	{
		if (write(STDOUT_FILENO, *args, ft_strlen(*args)) == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, EXIT_ERROR);
		if (*(args + 1) != NULL)
			if (write(STDOUT_FILENO, " ", 1) == -1)
				return (data->should_leave = true,
					data->with_which_code = MESSED_UP, EXIT_ERROR);
		args++;
	}
	if (newline)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, EXIT_ERROR);
	}
	return (EXIT_OK);
}

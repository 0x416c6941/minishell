/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:21:24 by root              #+#    #+#             */
/*   Updated: 2024/12/15 16:16:11 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <stddef.h>
#include <stdbool.h>
#include <utils.h>
#include <libft.h>

#define INVALID_ARG_EXIT_CODE	2

/**
 * Checks if *arg contains only digits and optional leading '+' or '-'
 * 	(as well as possible whitespaces).
 * @param	arg	Argument to check.
 * @return	(true), if yes;
 * 			(false) otherwise.
 */
static bool	ft_is_exit_arg_valid(const char *arg)
{
	while (ft_isspace(*arg))
		arg++;
	if (*arg == '+' || *arg == '-')
		arg++;
	if (*arg == '\0' || !ft_isdigit(*arg))
		return (false);
	while (ft_isdigit(*arg))
		arg++;
	while (ft_isspace(*arg))
		arg++;
	if (*arg != '\0')
		return (false);
	return (true);
}

int	exit_builtin(t_minishell_data *data, const char *args[])
{
	if (*args == NULL)
		return (data->should_leave = true,
			data->with_which_code = data->vars.last_exit_status, EXIT_OK);
	else if (args[1] != NULL)
	{
		if (ft_errmsg("exit: Too many arguments.\n") == -1)
		{
			data->should_leave = true;
			data->with_which_code = MESSED_UP;
		}
		return (EXIT_ERROR);
	}
	data->should_leave = true;
	if (!ft_is_exit_arg_valid(*args))
	{
		data->with_which_code = INVALID_ARG_EXIT_CODE;
		if (ft_errmsg("exit: numeric argument required\n") == -1)
			return (data->with_which_code = MESSED_UP , EXIT_ERROR);
		return (EXIT_OK);
	}
	data->with_which_code = ft_atoi(*args);
	return (EXIT_OK);
}

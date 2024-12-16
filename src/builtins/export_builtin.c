/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:29:58 by root              #+#    #+#             */
/*   Updated: 2024/12/16 16:17:10 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <stddef.h>
#include <utils.h>
#include <unistd.h>
#include <libft.h>
#include <stdlib.h>
#include <input_validation.h>

#define PRINT_PREFIX		"declare -x "

static int	ft_export_print_all(t_minishell_data *data)
{
	t_list	*env;

	env = data->vars.envs;
	while (env != NULL)
	{
		if (write(STDOUT_FILENO, PRINT_PREFIX, ft_strlen(PRINT_PREFIX)) == -1
			|| write(STDOUT_FILENO, ((t_env *)env->content)->key,
				ft_strlen(((t_env *)env->content)->key)) == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, EXIT_ERROR);
		if (((t_env *)env->content)->value != NULL)
		{
			if (write(STDOUT_FILENO, "=\"", sizeof("=\"") - 1) == -1
				|| write(STDOUT_FILENO, ((t_env *)env->content)->value,
					ft_strlen(((t_env *)env->content)->value)) == -1
				|| write(STDOUT_FILENO, "\"", 1) == -1)
				return (data->should_leave = true,
					data->with_which_code = MESSED_UP, EXIT_ERROR);
		}
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, EXIT_ERROR);
		env = env->next;
	}
	return (EXIT_OK);
}

int	export_builtin(t_minishell_data *data, const char *args[])
{
	int		ret;
	int		status;
	size_t	i;

	i = 0;
	if (*args == NULL)
		return (ft_export_print_all(data));
	ret = EXIT_OK;
	while (args[i] != NULL)
	{
		status = export_builtin_continuation(data, args[i]);
		if (status == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, EXIT_ERROR);
		else if (status == 0)
			ret = EXIT_ERROR;
		i++;
	}
	return (ret);
}

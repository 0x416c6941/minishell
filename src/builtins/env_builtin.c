/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:16:19 by root              #+#    #+#             */
/*   Updated: 2024/12/15 14:27:59 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <stddef.h>
#include <utils.h>
#include <unistd.h>
#include <libft.h>
#include <stdbool.h>

/**
 * Prints the variable in format "key=value".
 * @brief	Norminette bypass.
 * @param	env	Environment to print to stdout.
 * @return	(-1), if some write() failed;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_env_print_helper(const t_env *env)
{
	if (write(STDOUT_FILENO, env->key, ft_strlen(env->key)) == -1
		|| write(STDOUT_FILENO, "=", 1) == -1
		|| write(STDOUT_FILENO, env->value, ft_strlen(env->value)) == -1
		|| write(STDOUT_FILENO, "\n", 1) == -1)
		return (-1);
	return (0);
}

int	env_builtin(t_minishell_data *data, const char *args[])
{
	t_list	*node;
	t_env	*env;

	if (*args != NULL)
	{
		if (ft_errmsg("env: Too many arguments\n") == -1)
		{
			data->should_leave = true;
			data->with_which_code = MESSED_UP;
		}
		return (EXIT_ERROR);
	}
	node = data->vars.envs;
	while (node != NULL)
	{
		env = (t_env *)node->content;
		if (env->value != NULL)
		{
			if (ft_env_print_helper(env) == -1)
				return (data->should_leave = true,
					data->with_which_code = MESSED_UP, EXIT_ERROR);
		}
		node = node->next;
	}
	return (EXIT_OK);
}

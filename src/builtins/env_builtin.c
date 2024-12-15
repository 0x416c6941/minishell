/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:16:19 by root              #+#    #+#             */
/*   Updated: 2024/12/15 13:40:36 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <stddef.h>
#include <utils.h>
#include <unistd.h>
#include <libft.h>
#include <stdbool.h>

int	env_builtin(t_minishell_data *data, const char *args[])
{
	t_list	*node;
	t_env	*env;

	if (*args != NULL)
		return (EXIT_ERROR);
	node = data->vars.envs;
	while (node != NULL)
	{
		env = (t_env *)node->content;
		if (write(STDOUT_FILENO, env->key, ft_strlen(env->key)) == -1
			|| write(STDOUT_FILENO, "=", 1) == -1
			|| write(STDOUT_FILENO, env->value, ft_strlen(env->value)) == -1
			|| write(STDOUT_FILENO, "\n", 1) == -1)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, EXIT_ERROR);
		node = node->next;
	}
	return (EXIT_OK);
}

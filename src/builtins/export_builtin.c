/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:29:58 by root              #+#    #+#             */
/*   Updated: 2024/12/14 10:32:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

#define EXPORT_PREFIX "minishell: export: '"
#define EXPORT_ERROR "' not a valid identifier\n"

static void	export_err_msg(const char *msg)
{
	if (write(STDERR_FILENO, EXPORT_PREFIX, ft_strlen(EXPORT_PREFIX)) == -1)
		exit(EXIT_FATAL_ERROR);
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) == -1)
		exit(EXIT_FATAL_ERROR);
	if (write(STDERR_FILENO, EXPORT_ERROR, ft_strlen(EXPORT_ERROR)) == -1)
		exit(EXIT_FATAL_ERROR);
}

static int	write_env_variable(const char *prefix, t_env *env)
{
	if (write(STDOUT_FILENO, prefix, ft_strlen(prefix)) == -1)
		return (EXIT_FATAL_ERROR);
	if (write(STDOUT_FILENO, env->key, ft_strlen(env->key)) == -1)
		return (EXIT_FATAL_ERROR);
	if (env->value)
	{
		if (write(STDOUT_FILENO, "=\"", 2) == -1)
			return (EXIT_FATAL_ERROR);
		if (write(STDOUT_FILENO, env->value, ft_strlen(env->value)) == -1)
			return (EXIT_FATAL_ERROR);
		if (write(STDOUT_FILENO, "\"", 1) == -1)
			return (EXIT_FATAL_ERROR);
	}
	if (write(STDOUT_FILENO, "\n", 1) == -1)
		return (EXIT_FATAL_ERROR);
	return (EXIT_OK);
}

static int	export_no_args_builtin(const t_list *envs)
{
	const char		*prefix;
	const t_list	*current;
	t_env			*env;

	if (!envs)
		return (EXIT_OK);
	prefix = "declare -x ";
	current = envs;
	while (current)
	{
		env = (t_env *)current->content;
		if (!env || !env->key)
			return (EXIT_FATAL_ERROR);
		if (write_env_variable(prefix, env) == EXIT_FATAL_ERROR)
			return (EXIT_FATAL_ERROR);
		current = current->next;
	}
	return (EXIT_OK);
}

static int	add_env(t_list **env_head, const char *arg)
{
	t_ret		ft_initialize_one_env_status;
	t_list		*env_node;
	t_env		*new_env;
	const char	*unset_args[2];

	ft_initialize_one_env_status = ft_initialize_one_env(arg);
	if (ft_initialize_one_env_status.status == (-1))
		return (EXIT_FATAL_ERROR);
	env_node = ft_lstnew(ft_initialize_one_env_status.ret);
	if (env_node == NULL)
		return (EXIT_FATAL_ERROR);
	new_env = (t_env *)env_node->content;
	unset_args[0] = new_env->key;
	unset_args[1] = NULL;
	unset_builtin(env_head, unset_args);
	ft_lstadd_back(env_head, env_node);
	return (EXIT_OK);
}

int	export_builtin(t_list **env_head, const char **args)
{
	size_t	i;

	i = 0;
	if (!env_head || !args)
		return (EXIT_FATAL_ERROR);
	if (!args[0])
		return (export_no_args_builtin(*env_head));
	while (args[i] != NULL)
	{
		if (!is_valid_export_arg(args[i]))
		{
			export_err_msg(args[i]);
			i++;
			continue ;
		}
		if (add_env(env_head, args[i]) != EXIT_OK)
			return (EXIT_FATAL_ERROR);
		i++;
	}
	return (EXIT_OK);
}

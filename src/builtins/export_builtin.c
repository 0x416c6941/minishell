/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:29:58 by root              #+#    #+#             */
/*   Updated: 2024/12/12 17:41:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool	is_valid_export_arg(const char *arg)
{
	const char	*c;

	c = arg;
	if (!arg || ft_strchr(arg, '=') == NULL)
		return (false);
	if (!(arg[0] == '_' || ft_isalpha(arg[0])))
		return (false);
	while (*c != '=')
	{
		if (!(isalnum(*c) || *c == '_'))
			return (false);
		c++;
	}
	return (true);
}

static t_env	*create_env_variable(const char *key, const char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = ft_strdup(key);
	if (value)
		new_env->value = ft_strdup(value);
	else
		new_env->value = NULL;
	if (!new_env->key || (value && !new_env->value))
	{
		free(new_env->key);
		free(new_env->value);
		free(new_env);
		return (NULL);
	}
	return (new_env);
}

static int	update_env_variable(t_env *env, const char *value)
{
	char	*new_value;

	new_value = ft_strdup(value);
	if (!new_value)
		return (EXIT_FAILURE);
	free(env->value);
	env->value = new_value;
	return (EXIT_SUCCESS);
}

static int	add_env_to_list(t_vars *vars, t_env *new_env)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->content = new_env;
	new_node->next = vars->envs;
	vars->envs = new_node;
	return (EXIT_SUCCESS);
}

static int	parse_key_value(const char *arg, char **key, char **value)
{
	char	*key_end;
	size_t	key_len;

	key_end = strchr(arg, '=');
	if (!key_end)
		return (EXIT_FAILURE);
	key_len = key_end - arg;
	*key = strndup(arg, key_len);
	*value = ft_strdup(key_end + 1);
	if (!*key || !*value)
	{
		free(*key);
		free(*value);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	update_existing_variable(t_list *envs, const char *key,
		const char *value)
{
	t_list	*current;
	t_env	*env;

	current = envs;
	while (current)
	{
		env = (t_env *)current->content;
		if (strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			if (!env->value)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		current = current->next;
	}
	return (EXIT_FAILURE);
}

static int	safe_add_or_update_env(t_vars *vars, const char *arg)
{
	char	*key;
	char	*value;
	t_env	*new_env;

	key = NULL;
	value = NULL;
	new_env = NULL;
	if (parse_key_value(arg, &key, &value) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (update_existing_variable(vars->envs, key, value) == EXIT_SUCCESS)
	{
		free(key);
		free(value);
		return (EXIT_SUCCESS);
	}
	new_env = create_env_variable(key, value);
	free(key);
	free(value);
	if (!new_env || add_env_to_list(vars, new_env) != EXIT_SUCCESS)
	{
		free_env_variable(new_env);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	export_builtin(t_vars *vars, const char **args)
{
	size_t	i;

	i = 0;
	if (!vars || !args)
		return (EXIT_FAILURE);
	if (!args[0])
		return (export_no_args_builtin(vars));
	while (args[i] != NULL)
	{
		if (!is_valid_export_arg(args[i]))
		{
			i++;
			continue ;
		}
		if (add_or_update_env(vars, args[i]) != EXIT_SUCCESS)
		{
			if (write(2, EXPORT_ERROR, ft_strlen(EXPORT_ERROR)) == -1)
				return (EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

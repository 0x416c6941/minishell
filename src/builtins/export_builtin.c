/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:29:58 by root              #+#    #+#             */
/*   Updated: 2024/12/15 15:26:46 by asagymba         ###   ########.fr       */
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
#define EXPORT_ERR_PREFIX	"export: '"
#define EXPORT_ERR_POSTFIX	"': not a valid identifier\n"

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

/**
 * Returns an identifier exported from $arg.
 * @param	arg	Argument to export identifier from.
 * @return	A string containing an identifier;
 * 			or (NULL) in case of malloc() fail.
 */
static char	*ft_get_identifier(const char *arg)
{
	char	*ret;
	size_t	key_len;

	key_len = ft_strcspn(arg, "=");
	ret = (char *)malloc(key_len + 1);
	if (ret == NULL)
		return (NULL);
	(void)ft_strlcpy(ret, arg, key_len + 1);
	return (ret);
}

/**
 * Prints an error to stderr.
 * @param	identifier	Invalid identifier to write to stderr.
 * @return	(-1), if some write() failed;
 * 			(Some non-negative value) otherwise.
 */
static int	export_err_msg(const char *identifier)
{
	if (ft_errmsg(EXPORT_ERR_PREFIX) == -1
		|| write(STDERR_FILENO, identifier, ft_strlen(identifier)) == -1
		|| write(STDERR_FILENO, EXPORT_ERR_POSTFIX,
			ft_strlen(EXPORT_ERR_POSTFIX)) == -1)
		return (-1);
	return (0);
}

/**
 * Adds or modifies an environment variable, contained in $arg
 * (with identifier $identifier) to / in $data.
 * @param	data		Minishell's data.
 * @param	arg			Argument to add or modify.
 * @param	identifier	Identifier of the argument.
 * @return	(-1), if something went wrong;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_add_or_modify_env(t_minishell_data *data, const char *arg,
		const char *identifier)
{
	t_env	*saved;
	t_ret	status;
	t_list	*to_append;

	saved = ft_find_env(data->vars.envs, identifier);
	if (saved != NULL)
	{
		if (arg[ft_strlen(identifier)] == '=')
		{
			free(saved->value);
			saved->value = ft_strdup(arg + ft_strlen(identifier) + 1);
			if (saved->value == NULL)
				return (-1);
		}
		return (0);
	}
	status = ft_initialize_one_env(arg);
	if (status.status == -1)
		return (-1);
	to_append = ft_lstnew(status.ret);
	if (to_append == NULL)
		return (ft_free_t_env(status.ret), -1);
	ft_lstadd_back(&data->vars.envs, to_append);
	return (0);
}

int	export_builtin(t_minishell_data *data, const char *args[])
{
	size_t	i;
	char	*identifier;

	i = 0;
	if (*args == NULL)
		return (ft_export_print_all(data));
	while (args[i] != NULL)
	{
		identifier = ft_get_identifier(args[i]);
		if (identifier == NULL)
			return (data->should_leave = true,
				data->with_which_code = MESSED_UP, EXIT_ERROR);
		if (!ft_is_valid_export_identifier(identifier))
		{
			if (export_err_msg(args[i++]) == -1)
				return (free(identifier), data->should_leave = true,
					data->with_which_code = MESSED_UP, EXIT_ERROR);
			free(identifier);
			continue ;
		}
		if (ft_add_or_modify_env(data, args[i++], identifier) != EXIT_OK)
			return (free(identifier), EXIT_ERROR);
		free(identifier);
	}
	return (EXIT_OK);
}

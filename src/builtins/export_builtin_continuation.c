/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin_continuation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:29:58 by root              #+#    #+#             */
/*   Updated: 2024/12/16 16:19:23 by asagymba         ###   ########.fr       */
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

#define EXPORT_ERR_PREFIX	"export: '"
#define EXPORT_ERR_POSTFIX	"': not a valid identifier\n"

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

int	export_builtin_continuation(t_minishell_data *data, const char *arg)
{
	char	*identifier;

	identifier = ft_get_identifier(arg);
	if (identifier == NULL)
		return (-1);
	if (!ft_is_valid_export_identifier(identifier))
	{
		if (export_err_msg(arg) == -1)
			return (free(identifier), -1);
		free(identifier);
		return (0);
	}
	if (ft_add_or_modify_env(data, arg, identifier) == -1)
		return (free(identifier), -1);
	free(identifier);
	return (1);
}

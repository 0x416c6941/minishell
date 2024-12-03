/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_expanded_arg_size.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:33:14 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/03 15:06:10 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <utils.h>
#include <stddef.h>
#include <parse.h>
#include <stdlib.h>

/**
 * Handles quotes and, if $quotes_type doesn't change, increases *$ret by 1.
 * @param	quote		Quote to handle.
 * @param	quotes_type	Pointer to the current quote type.
 * @param	ret			Pointer to the current size of the expanded argument.
 */
static void	ft_handle_quote_and_update_ret(char quote,
		enum e_quotes_type *quotes_type, size_t *ret)
{
	enum e_quotes_type	new_quotes_type;

	new_quotes_type = *quotes_type;
	ft_handle_quotes(quote, &new_quotes_type);
	if (new_quotes_type == *quotes_type)
		(*ret)++;
	*quotes_type = new_quotes_type;
}

/**
 * If $quotes_type isn't "single_quote",\
 * 	increases *$ret by the size of the variable's value stored in $arg
 * 	and shifts *$arg by the size of the variable's name stored in $arg.
 * If *$arg doesn't contain a valid variable,
 * 	*$ret and *$arg are increased by 1.
 * If $quotes_type is "single_quote", increases *$ret and *$arg by 1.
 * @brief	Stupid Norminette bypass.
 * @param	vars		Pointer to structure containing last exit status
 * 						and environment variables in a key-pair structure.
 * @param	arg			Pointer to manipulate current position in the argument.
 * @param	quotes_type	Current quote type.
 * @param	ret			Pointer to the current size of the expanded argument.
 * @return	(-1), if some malloc failed;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_var_helper(const t_vars *vars,
		const char **arg, enum e_quotes_type quotes_type, size_t *ret)
{
	t_ret	ft_extract_var_name_status;
	char	*var_value;

	if (quotes_type == single_quote)
	{
		(*arg)++;
		(*ret)++;
		return (0);
	}
	ft_extract_var_name_status = ft_extract_var_name(*arg);
	if (ft_extract_var_name_status.status == -1)
		return (-1);
	else if (ft_extract_var_name_status.status == 0)
	{
		(*arg)++;
		(*ret)++;
		return (0);
	}
	var_value = ft_get_env_value(vars, ft_extract_var_name_status.ret);
	if (var_value == NULL)
		return (free(ft_extract_var_name_status.ret), -1);
	return (*arg += ft_strlen(ft_extract_var_name_status.ret) + 1,
		*ret += ft_strlen(var_value) + 1,
		free(ft_extract_var_name_status.ret), free(var_value), 0);
}

t_ret	ft_calculate_expanded_arg_size(const t_vars *vars, const char *arg)
{
	size_t				*ret;
	enum e_quotes_type	quotes;

	ret = (size_t *)ft_calloc(1, sizeof(size_t));
	if (ret == NULL)
		return ((t_ret){(-1), NULL});
	quotes = no_quotes;
	while (*arg != '\0')
	{
		if (*arg == '\'' || *arg == '\"')
		{
			ft_handle_quote_and_update_ret(*arg, &quotes, ret);
			arg++;
			continue ;
		}
		else if (*arg == '$')
		{
			if (ft_var_helper(vars, &arg, quotes, ret) == -1)
				return (free(ret), (t_ret){(-1), NULL});
			continue ;
		}
		arg++;
		(*ret)++;
	}
	return ((*ret)++, (t_ret){0, ret});
}

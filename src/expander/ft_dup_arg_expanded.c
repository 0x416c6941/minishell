/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_arg_expanded.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:30:06 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/03 16:22:08 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <parse.h>
#include <utils.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * Handles quotes and, if $quotes_type doesn't change, writes them to *$ret,
 * while increasing *$ret by 1 (shifting it to the byte in a buffer).
 * Literally a duplicate of ft_handle_quote_and_update_ret().
 * @param	quote		Quote to handle.
 * @param	quotes_type	Pointer to the current quote type.
 * @param	ret			Pointer to the buffer.
 */
static void	ft_handle_quote_and_write_them_to_ret(char quote,
		enum e_quotes_type *quotes_type, char **ret)
{
	enum e_quotes_type	new_quotes_type;

	new_quotes_type = *quotes_type;
	ft_handle_quotes(quote, &new_quotes_type);
	if (new_quotes_type == *quotes_type)
		*((*ret)++) = quote;
	*quotes_type = new_quotes_type;
}

/**
 * If $quotes_type isn't "single_quote", writes
 * 	variable's value stored in *$arg to *$ret
 * 	and shifts *$ret by the size of the variable's value stored in *$arg
 * 		and *$arg by the (size of the variable's name stored in *$arg + 1).
 * If *$arg doesn't contain a valid variable,
 * 	writes '$' to *$ret and shifts both *$ret and *$arg by 1.
 * If $quotes_type is "single_quote",
 * 	writes **$arg to **$ret and shifts both *$ret and *$arg by 1.
 * Literally a duplicate of ft_var_helper()
 * 	from src/expander/ft_calculate_expanded_arg_size.c.
 * @brief	Stupid Norminette bypass.
 * @param	vars		Pointer to structure containing last exit status
 * 						and environment variables in a key-pair structure.
 * @param	arg			Pointer to manipulate current position in the argument.
 * @param	quotes_type	Current quote type.
 * @param	ret			Pointer to the buffer.
 * @return	(-1), if some malloc failed;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_var_helper(const t_vars *vars,
		const char **arg, enum e_quotes_type quotes_type, char **ret)
{
	t_ret	ft_extract_var_name_status;
	char	*var_value;

	if (quotes_type == single_quote)
		return (*((*ret)++) = *((*arg)++), 0);
	ft_extract_var_name_status = ft_extract_var_name(*arg);
	if (ft_extract_var_name_status.status == -1)
		return (-1);
	else if (ft_extract_var_name_status.status == 0)
		return (*((*ret)++) = '$', *arg += 1, 0);
	var_value = ft_get_env_value(vars, ft_extract_var_name_status.ret);
	if (var_value == NULL)
		return (free(ft_extract_var_name_status.ret), -1);
	(void)ft_memcpy(*ret, var_value, ft_strlen(var_value));
	return (*ret += ft_strlen(var_value),
		*arg += ft_strlen(ft_extract_var_name_status.ret) + 1,
		free(ft_extract_var_name_status.ret), free(var_value), 0);
}

/**
 * Fills $ret with the expanded version of $arg.
 * Mostly a duplicate of ft_calculate_expanded_arg_size().
 * @brief	Stupid Norminette bypass.
 * @param	vars	Pointer to structure containing last exit status
 * 					and environment variables in a key-pair structure.
 * @param	arg		Argument to be expanded.
 * @param	ret		Pointer to the buffer where the expanded argument
 * 					will be written.
 * @return	(-1), if some malloc() failed;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_dup_arg_expanded_helper(const t_vars *vars, const char *arg,
		char *ret)
{
	enum e_quotes_type	quotes;

	quotes = no_quotes;
	while (*arg != '\0')
	{
		if (*arg == '\'' || *arg == '\"')
		{
			ft_handle_quote_and_write_them_to_ret(*arg, &quotes, &ret);
			arg++;
			continue ;
		}
		else if (*arg == '$')
		{
			if (ft_var_helper(vars, &arg, quotes, &ret) == -1)
				return (-1);
			continue ;
		}
		*ret++ = *arg++;
	}
	return (*ret = '\0', 0);
}

t_ret	ft_dup_arg_expanded(const t_vars *vars, const char *arg)
{
	t_ret	status;
	char	*ret;

	status = ft_calculate_expanded_arg_size(vars, arg);
	if (status.status == -1)
		return ((t_ret){(-1), NULL});
	ret = (char *)malloc(*((size_t *)status.ret));
	free(status.ret);
	if (ret == NULL)
		return ((t_ret){(-1), NULL});
	else if (ft_dup_arg_expanded_helper(vars, arg, ret) == -1)
		return (free(ret), (t_ret){(-1), NULL});
	return ((t_ret){0, ret});
}

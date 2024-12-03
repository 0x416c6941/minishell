/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:01:20 by root              #+#    #+#             */
/*   Updated: 2024/12/03 10:56:01 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <stddef.h>
#include <libft.h>
#include <stdlib.h>

/**
 * @brief	Calculates the length of a standard variable name.
 * @param	read_ptr Pointer to the start of the variable name.
 * @return	Length of the variable name;
 * 			(0) if invalid (empty or contains e.g. ':' immediately).
 */
static size_t	ft_get_standard_var_len(const char *read_ptr)
{
	size_t	var_len;

	var_len = 0;
	while ((*read_ptr >= 'a' && *read_ptr <= 'z')
		|| (*read_ptr >= 'A' && *read_ptr <= 'Z')
		|| (*read_ptr >= '0' && *read_ptr <= '9')
		|| *read_ptr == '_')
	{
		var_len++;
		read_ptr++;
	}
	return (var_len);
}

t_ret	ft_extract_var_name(const char *read_ptr)
{
	char	*ret;
	size_t	var_len;

	if (*read_ptr++ != '$')
		return ((t_ret){0, NULL});
	if (*read_ptr == '?')
	{
		ret = ft_strdup("?");
		if (ret == NULL)
			return ((t_ret){(-1), NULL});
		return ((t_ret){1, ret});
	}
	var_len = get_standard_var_len(read_ptr);
	if (var_len == 0)
		return ((t_ret){0, NULL});
	ret = (char *)malloc(var_len + 1);
	if (ret == NULL)
		return ((t_ret){(-1), NULL});
	(void)strlcpy(ret, read_ptr, var_len + 1);
	return ((t_ret){1, ret});
}

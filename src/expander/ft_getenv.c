/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:55:25 by root              #+#    #+#             */
/*   Updated: 2024/11/29 15:56:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

/**
 * @brief Retrieves the value of an environment variable or `$?` for exit code.
 *
 * @param name The variable name, `$?` returns the last exit code.
 * @return char* Dynamically allocated string of the variable's value, or NULL.
 */
char	*ft_getenv(const char *name)
{
	char	*res;
	char	*itoa_result;

	if (name == NULL)
		return (ft_strdup(""));
	if (ft_strcmp(name, "?") == 0)
	{
		itoa_result = ft_itoa(g_exit_code);
		if (itoa_result == NULL)
			return (NULL);
		res = ft_strdup(itoa_result);
		free(itoa_result);
		return (res);
	}
	res = getenv(name);
	if (res == NULL)
		return (ft_strdup(""));
	return (ft_strdup(res));
}

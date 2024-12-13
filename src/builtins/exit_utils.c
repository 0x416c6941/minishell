/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:02:23 by root              #+#    #+#             */
/*   Updated: 2024/12/13 20:02:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

/**
 * @brief Parses the sign, skips whitespace,
	and returns a pointer to the number.
 *
 * @param nptr Pointer to the string to parse.
 * @param sign Pointer to an integer where the sign (+1 or -1) will be stored.

 * @return const char* Pointer to the remaining part of the string after parsing
 */
const char	*parse_sign_and_skip_whitespace(const char *nptr, int *sign)
{
	*sign = 1;
	if (!nptr)
		return (NULL);
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			*sign = -1;
		nptr++;
	}
	return (nptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:20:38 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/30 23:46:33 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/**
 * ---------------------------------------------------------------------------
 * structs.
 * ---------------------------------------------------------------------------
 */
/**
 * Wrapper primarily to catch malloc() fails.
 * $ret may be whatever, including e.g. ints casted to uintptr_t.
 */
typedef struct s_ret
{
	/**
		* $status values meaning:
		* 	(-1): error that should lead to exit of minishell;
		* 	Non-negative value: can proceed as normal.
		* 		Those however can be further adjusted
		* 		depending on the indivial functions.
		*/
	int		status;
	void	*ret;
}	t_ret;

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * Shifts *str to the first non-space character.
 * @param	str	A pointer to string.
 */
void	ft_skip_spaces(const char **str);

#endif /* UTILS_H */

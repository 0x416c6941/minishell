/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:20:38 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/01 00:45:03 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/**
 * ---------------------------------------------------------------------------
 * Constants.
 * ---------------------------------------------------------------------------
 */
# define MINISHELL_PREFIX	"minishell: "

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

/**
 * Writes an error message to stderr.
 * @param	msg	The message to write.
 * @return	(-1) if got some I/O error;
 * 			(Some non-negative value) otherwise.
 */
int		ft_errmsg(const char *msg);

/**
 * @brief	Checks if the string contains only whitespace characters.
 * @param	str	Input to check.
 * @return	(Some non-zero value) if yes;
 * 			(0) otherwise.
 */
int		ft_input_issspace(const char *str);

#endif /* UTILS_H */

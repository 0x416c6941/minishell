/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:28:06 by root              #+#    #+#             */
/*   Updated: 2024/12/03 13:22:28 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <utils.h>
# include <libft.h>
# include <stddef.h>
# include <parse.h>

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * @brief	Extracts the variable name starting at $read_ptr.
 * @warning	Dynamic memory allocation is used.
 * @param	read_ptr	Pointer that stores the variable name.
 * @return	If ($status == (-1)), then malloc() failed and $ret is NULL;
 * 			if ($status == 0), then user has entered incorrect variable name,
 * 				$ret will be NULL in this case;
 * 			otherwise $status will be some positive value,
 * 				and $ret will contain a variable name as a string.
 */
t_ret		ft_extract_var_name(const char *read_ptr);

/**
 * @brief	Retrieves the value of an environment variable
 * 			or exit code for "$?".
 * @warning	Dynamic memory allocation is used.
 * @param	vars	Pointer to structure containing last exit status 
 * 					and environment variables in a key-pair structure.
 * @param	key		The variable name, "$?" returns the last exit code.
 * @return	Dynamically allocated string of the variable's value,
 * 			(NULL) if some malloc() went awfully wrong.
 */
char		*ft_getenv(const t_vars *vars, const char *key);

/**
 * Since we don't work with normal resizeable strings,
 * let's first calculate the length of the buffer where we will
 * write expanded argument.
 * @brief	Calculates length of the buffer for expanded argument.
 * @warning	Dynamic memory allocation is used.
 * @param	vars	Pointer to structure containing last exit status 
 * 					and environment variables in a key-pair structure.
 * @param	arg		Argument to be expanded.
 * @return	If $status == (-1), then some malloc() failed;
 * 			otherwise $status will be non-negative value and
 * 				$ret will contain a size_t with the buffer's calculated length.
 */
t_ret		ft_calculate_expanded_arg_size(const t_vars *vars, const char *arg);

/**
 * Makes a duplicate of $arg with everything expanded.
 * @warning	Dynamic memory allocation is used.
 * @param	vars	Pointer to structure containing last exit status 
 * 					and environment variables in a key-pair structure.
 * @param	arg		Argument to be expanded.
 * @return	If $status == (-1), then some malloc() failed;
 * 			otherwise $status will be non-negative value and
 * 				$ret will contain a duplicate of $arg with everything expanded.
 */
t_ret	ft_dup_arg_expanded(const t_vars *vars, const char *arg)

#endif /* EXPANDER_H */

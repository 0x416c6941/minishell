/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:28:06 by root              #+#    #+#             */
/*   Updated: 2024/12/03 12:23:16 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <utils.h>
# include <libft.h>
# include <stddef.h>

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
 */
t_ret		ft_expand_arg(const char *arg);

t_ret		*ft_process_args(const char *content);

/**
 * @brief	Replaces a variable with its value in the output buffer.
 * @param	var_name		The name of the variable to replace.
 * @param	buffer			Pointer to the output buffer.
 * @param	write_offset	Pointer to the current write offset in the buffer.
 * @param	buffer_size		Pointer to the current size of the buffer.
 * @return	The length of the appended value;
 * 			(0) on failure.
 */
size_t		replace_var_with_value(const char *var_name, char **buffer,
				size_t *write_offset, size_t *buffer_size);

/**
 * @brief	Removes outer quotes from the string and copies the content
 *			into `dest`.
 * @param	dest	Pointer to the destination buffer.
 * @param	src		Pointer to the source string.
 */
void		remove_quotes(char *dest, const char *src);

#endif /* EXPANDER_H */

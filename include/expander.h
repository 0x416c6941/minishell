/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:28:06 by root              #+#    #+#             */
/*   Updated: 2024/11/30 00:19:53 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <libft.h>
# include <parse.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define EXPAND_VAR_ERROR	-1
# define EXPAND_VAR_SUCCESS	1

extern int	g_exit_code;

t_ret		*ft_process_args(const char *content);
int			expand_var(char *str);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, size_t n);
void		ft_print_error(const char *error_message);

/**
 * @brief	Retrieves the value of an environment variable or `$?` for exit
 *			code.
 * @warning	Dynamic memory allocation is used.
 * @param	name	The variable name, `$?` returns the last exit code.
 * @return	Dynamically allocated string of the variable's value,
 * 			(NULL) if some malloc() went awfully wrong.
 */
char		*ft_getenv(const char *name);

/**
 * @brief	Extracts the variable name starting at `read_ptr`.
 *
 * @param	read_ptr	Pointer to the variable name.
 * @param	var_name	Pointer to store the allocated variable name.
 * @return	Length of the variable name;
 * 			(0) on failure.
 */
size_t		extract_var_name(const char *read_ptr, char **var_name);

/**
 * @brief	Replaces a variable with its value in the output buffer.
 *
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
 *
 * @param	dest	Pointer to the destination buffer.
 * @param	src		Pointer to the source string.
 */
void		remove_quotes(char *dest, const char *src);

#endif /* EXPANDER_H */

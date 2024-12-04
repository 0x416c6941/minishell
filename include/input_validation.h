/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:35:47 by root              #+#    #+#             */
/*   Updated: 2024/12/04 19:22:40 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_VALIDATION_H
# define INPUT_VALIDATION_H

/**
 * ---------------------------------------------------------------------------
 * Constants.
 * ---------------------------------------------------------------------------
 */
# define ERR_UNSUPPORTED	"owo... ||, &, &&, ; and \\ are n0t suppowwted :c\n"
# define ERR_PIPE_START		"i'm sad... got unexpected token '|' :(((\n"
# define ERR_PIPE_END		"UwU got unexpected EOF (newline) :(((\n"

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * Checks if $str contains any of the unsupported characters:
 * 	||, &, &&, ; and \.
 * If it does, then error message is also generated to stderr by using
 * ft_errmsg().
 * @brief	Check for unsupported characters and generate error message
 * 			if any is found.
 * @param	str	The string to check.
 * @return	(Some positive value), if no unsupported characters are found;
 * 			(0), if unsupported characters and error message was successfully
 * 				written to stderr;
 * 			(-1), if write to stderr has failed.
 */
int	ft_check_unsupported(const char *str);

/**
 * Check for invalid pipe positions in the beginning or in the end of $str.
 * @param	str	String to check.
 * @return	(-1) if found invalid pipe;
 * 			(Some non-negative value) otherwise;
 */
int	ft_has_invalid_pipe_position(const char *str);

#endif /* INPUT_VALIDATION_H */

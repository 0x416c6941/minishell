/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:35:47 by root              #+#    #+#             */
/*   Updated: 2024/12/01 00:31:16 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_VALIDATION_H
# define INPUT_VALIDATION_H

/**
 * ---------------------------------------------------------------------------
 * Constants.
 * ---------------------------------------------------------------------------
 */
# define ERR_UNSUPPORTED "||, &, &&, ; and \\ are unsupported.\n"

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

#endif /* INPUT_VALIDATION_H */

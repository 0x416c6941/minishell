/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:54:13 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 12:23:16 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

/**
 * ---------------------------------------------------------------------------
 * Structures, unions and enums.
 * ---------------------------------------------------------------------------
 */
/**
 * A helper structure. During parsing, arguments will be saved here,
 * the final result will be then moved to $args in t_exec.
 */
typedef struct t_arg
{
	char			*arg;
	struct t_arg	*next;
}	t_arg;

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * A modified version of ft_strtok_r(), which tokenizes prompt
 * by '|' delimiters and doesn't clear consecutive delimiters.
 *
 * Usage is similar to ft_strtok_r(): in each subsequent call that
 * parses the same prompt, $prompt must be NULL.
 * @brief	Tokenizes prompt by '|' delimiters.
 * @param	prompt	The string to tokenize.
 * @param	saveptr	Where to save the current position.
 * @return	The next token;
 * 			NULL if there are no more tokens.
 */
char	*ft_get_next_token(char *prompt, char **saveptr);

#endif	/* PARSE_UTILS_H */

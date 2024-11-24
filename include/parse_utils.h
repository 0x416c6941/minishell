/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:54:13 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 12:28:12 by asagymba         ###   ########.fr       */
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

#endif	/* PARSE_UTILS_H */

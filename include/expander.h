/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:28:06 by root              #+#    #+#             */
/*   Updated: 2024/12/04 18:50:33 by asagymba         ###   ########.fr       */
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
t_ret	ft_extract_var_name(const char *read_ptr);

/**
 * @brief	Retrieves the value of an environment variable
 * 			or exit code for "$?".
 * @warning	Dynamic memory allocation is used.
 * @param	vars	Pointer to structure containing last exit status
 * 					and environment variables in a key-pair structure.
 * @param	key		The variable name, "$?" returns the last exit code.
 * @return	Dynamically allocated string of the variable's value;
 * 			(NULL) if some malloc() went awfully wrong.
 */
char	*ft_get_env_value(const t_vars *vars, const char *key);

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
t_ret	ft_calculate_expanded_arg_size(const t_vars *vars, const char *arg);

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
t_ret	ft_dup_arg_expanded(const t_vars *vars, const char *arg);

/**
 * Checks, if $arg consists of variables only.
 * @param	arg	Argument to check.
 * @return	(-1), if malloc() failed;
 * 			(0), if $arg consists of something else as well;
 * 			(Some positive value) if it does.
 */
int		ft_is_whole_arg_var(const char *arg);

/**
 * Expands everything in $exec_to_expand:
 * 	first of all, $args will be expanded to $args_for_execve,
 * 		and then $args will be freed and to NULL;
 * 	next all nodes in $stdin_redirs and $stdout_redirs will be expanded
 * 		(old unexpanded versions will be freed).
 * @brief	Expands everything in $exec_to_expand.
 * @warning	Dynamic memory allocation is used.
 * @param	vars			Pointer to structure containing last exit status
 * 							and environment variables in a key-pair structure.
 * @param	exec_to_expand	"t_exec" parsed command to expand.
 * @return	(-1), if something went wrong;
 * 			(AMBIGIOUS_REDIRECT), if some redirections are ambigious;
 * 			(CMD_OK) if everything went fine.
 */
int		ft_expand_t_exec(const t_vars *vars, t_exec *exec_to_expand);

/**
 * Basically just removes all quotes in $heredoc_delim.
 * @param	heredoc_delim	Heredoc's delimeter in which to remove all quotes.
 */
void	ft_expand_heredoc_delim(char *heredoc_delim);

#endif /* EXPANDER_H */

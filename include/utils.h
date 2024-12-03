/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:20:38 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/03 11:01:28 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <libft.h>

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
 * Basically a map-like structure, however only for one key-value pair.
 */
typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

/**
 * Main data structure.
 *
 * Unfortunalely, since neither $environ nor putenv() can be used,
 * we need to use an $envp, which isn't a universally accepted standard,
 * and later divide it to a structure we'd be able to manipulate with.
 */
typedef struct s_vars
{
	int		last_exit_status;
	t_list	*envs;				/* $content is a t_env in each node. */
}	t_vars;

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

/**
 * Transforms $envp to a linked list, all nodes of which can be freed,
 * including it's content (which is of "t_env" type).
 * @brief	Transforms $envp to a linked list.
 * @warning	Dynamic memory allocation is used.
 * @param	envp	Environment pointer.
 * @return	If $status is (-1), then malloc() failed and $ret will be NULL;
 * 			in all other cases $status is a non-negative value,
 * 				and $ret contains a head of the linked list
 * 				with each environment variable saved as t_env.
 */
t_ret	ft_initialize_envs(const char **envp);

/**
 * Frees a t_env.
 * @param	t_env	Pointer to t_env to free.
 */
void	ft_free_t_env(t_env *env);

#endif /* UTILS_H */

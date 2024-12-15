/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:20:38 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/15 14:58:01 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <libft.h>
# include <stdbool.h>

/**
 * ---------------------------------------------------------------------------
 * Constants.
 * ---------------------------------------------------------------------------
 */
# define MINISHELL_PREFIX "minishell: "

/**
 * ---------------------------------------------------------------------------
 * enums.
 * ---------------------------------------------------------------------------
 */
enum	e_quotes_type
{
	no_quotes,
	single_quote,
	double_quotes,
};

/**
 * ---------------------------------------------------------------------------
 * structs.
 * ---------------------------------------------------------------------------
 */
/**
 * Wrapper primarily to catch malloc() fails.
 * Please note, that $ret, if not NULL, should always be freed,
 * 	otherwise memory leak would occur.
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
 * Unfortunalely, since neither $environ nor putenv() can be used,
 * we need to use an $envp, which isn't a universally accepted standard,
 * and later split it into a structure we'd be able to manipulate with.
 * In each node of envs, $content is a t_env.
 */
typedef struct s_vars
{
	int		last_exit_status;
	t_list	*envs;
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
 * Depending on the quote in $quote,
 * updates what quote we currently have open.
 * @param	quote		Quote to handle.
 * @param	quotes_type	A pointer to the current quote type.
 */
void	ft_handle_quotes(char quote, enum e_quotes_type *quotes_type);

/**
 * Writes an error message to stderr.
 * @param	msg	The message to write.
 * @return	((-1) if got some I/O error);
 * 			(Some non-negative value) otherwise.
 */
int		ft_errmsg(const char *msg);

/**
 * @brief	Checks if the string contains only whitespace characters.
 * @param	str	Input to check.
 * @return ((Some non-zero value) if yes);
 * 			(0) otherwise.
 */
int		ft_input_issspace(const char *str);

/**
 * Initialize a single node contaning t_env with environment variable.
 * Please note, that if $env doesn't contain a '=', then $ret->value
 * 	will be NULL (and it won't show in the `$ env` builtin,
 * 		but only in the `$ export` one).
 * @warning	Dyamic memory allocation is used.
 * @param	env	Environment variable.
 * @return (If $status is (-1), then malloc() failed and $ret is NULL);
 * 			Otherwise $status is non-negative value, and $ret
 * 				contains a t_env with environment variable.
 */
t_ret	ft_initialize_one_env(const char *env);

/**
 * Transforms $envp to a linked list, all nodes of which can be freed,
 * including it's content (which is of "t_env" type).
 * @brief	Transforms $envp to a linked list.
 * @warning	Dynamic memory allocation is used.
 * @param	envp	Environment pointer.
 * @return	(If $status is (-1),
 * 			then malloc() failed and $ret will be NULL);
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

/**
 * Looks for an environment variable with key $identifier in $env
 * 	(which is an $envs from t_vars).
 * @param	env			Environment variables.
 * @param	identifier	Key to look for.
 * @return	(Found environment variable) or (NULL), if not found.
 */
t_env	*ft_find_env(t_list *env, const char *identifier);

/* Function to calculate the number of elements in const char *args[] */
/* size_t	calculate_args_count(const char *args[]); */

#endif /* UTILS_H */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:39:32 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/14 23:44:36 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <utils.h>

/**
 * ---------------------------------------------------------------------------
 * Constants.
 * ---------------------------------------------------------------------------
 */
# define BAD_MSG	"uwu, malloc()-san or I/O fa1led ;(((\n"
# define MESSED_UP	1

# define MINISHELL_INPUT_INCORRECT	0
# define MINISHELL_INPUT_EOF		1
# define MINISHELL_INPUT_OK			2

/**
 * ---------------------------------------------------------------------------
 * structs.
 * ---------------------------------------------------------------------------
 */
/**
 * Structure with all data Minishell would use.
 */
typedef struct s_minishell_data
{
	t_vars		vars;
	const bool	is_interactive;
	t_list		*parser_result;
	/**
	 * Since we'll overwrite STDIN_FILENO and STDOUT_FILENO
	 * when executable builtins, we'll need to preserve real file descriptors.
	 */
	int			real_stdin_fd;
	int			real_stdout_fd;
	bool		should_leave;
	int			with_which_code;
}	t_minishell_data;

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * Initializes Minishell's data.
 * @warning	Dynamic memory allocation is used.
 * @param	data	Where to initialize the data.
 * @return	(-1), if some malloc() failed;
 * 			(Some non-negative value) otherwise.
 */
int		ft_init_data(const char **envp, t_minishell_data *data);

/**
 * free()'s Minishell's data and clears readline's history.
 * @param	data	Minishell's data to free().
 * @return	(-1), if some close() failed;
 * 			(Some non-negative value) otherwise.
 */
int		ft_free_data(t_minishell_data *data);

/**
 * Gets a prompt from user and divides it into execs by running parser on it.
 * @param	data	Minishell's data.
 * @return	(-1), if something went wrong and we should leave;
 * 			(MINISHELL_INPUT_EOF), if input was EOF;
 * 			(MINISHELL_INPUT_INCORRECT), if input was incorrect;
 * 			(MINISHELL_INPUT_OK) otherwise.
 */
int		ft_get_execs(t_minishell_data *data);

/**
 * Literally Minishell.
 * @param	data	Minishell's initialized data.
 * @return	Literally garbage. return()'s some data just to bypass Norminette.
 */
int		minishell(t_minishell_data *data);

/**
 * Prepares environment (handles all stdin and stdout redirections)
 * and executes the entered commands (t_execs).
 */
int		ft_prep_env_and_exec(t_minishell_data *data);

#endif /* MINISHELL_H */

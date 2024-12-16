/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:39:32 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/16 01:29:50 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <utils.h>
# include <parse.h>

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
 * Handles all stdin and stdout redirections.
 * If some redirection or I/O fails, error log will be written to stderr.
 * @param	cmd	Command to handle redirections of.
 * @return	(-1), if something went wrong;
 * 			(Some non-negative value) otherwise.
 */
int		ft_handle_redirs(t_exec *cmd);

/**
 * Restores original stdin and stdout fds.
 * @param	data	Minishell's data.
 * @return	(-1), if something went wrong and we should leave;
 * 			(Some non-negative value) otherwise.
 */
int		ft_restore_stdin_stdout(t_minishell_data *data);

/**
 * Executes builtin.
 * @param	cmd	Command to execute.
 * @return	Please refer to an individual builtin's documentation.
 */
int		ft_exec_builtin(t_minishell_data *data, t_exec *cmd);

/**
 * Prepares environment (handles all stdin and stdout redirections)
 * and executes the entered commands (t_execs).
 * After calling this function, Minishell would exit.
 * @param	data	Minishell's data.
 * @return	(-1), if something went wrong and we should leave:
 * 				this includes really important system calls,
 * 				such as fork(), pipe(), etc., which should never fail;
 * 			(Some non-negative value) is returned otherwise.
 */
int		ft_prep_env_and_exec(t_minishell_data *data);

/**
 * Executor.
 * After execution is finished, original stdin and stdout fds are restored.
 * @param	data	Minishell's data.
 * @return	(-1), if something went wrong and we should leave;
 * 			(Some non-negative value) is returned otherwise.
 */
int		ft_execute(t_minishell_data *data);

/**
 * Checks syntax and executes the parsed commands.
 * Also frees the parser result, so that no memory leaks occur.
 * If ft_are_there_syntax_errors_in_parsed_cmd() returns -1,
 * 	data->should_leave will be set to true,
 * 	and data->with_which_code will be set to MESSED_UP.
 * @param	data	Minishell's data.
 */
void	ft_check_syntax_and_execute(t_minishell_data *data);

/**
 * Prepares envp for execve().
 * Can be free()'d with ft_split_free() from Libft.
 * @param	data	Minishell's data.
 * @return	An array of strings for execve(),
 * 			or NULL if malloc() failed.
 */
char	**ft_prepare_envp(t_minishell_data *data);

#endif /* MINISHELL_H */

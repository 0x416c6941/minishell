/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:51:34 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/03 16:10:08 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <libft.h>
# include <utils.h>

/**
 * ---------------------------------------------------------------------------
 * Constants.
 * ---------------------------------------------------------------------------
 */
# define ARG_IS_EMPTY				0
# define UNCLOSED_SINGLE_QUOTE		1
# define UNCLOSED_DOUBLE_QUOTES		2
# define UNFINISHED_STDIN_REDIR		3
# define UNFINISHED_STDOUT_REDIR	4
# define INAPPROPRIATE_STDIN_REDIR	5
# define INAPPROPRIATE_STDOUT_REDIR	6
# define AMBIGIOUS_REDIRECT			7
# define ARG_OK						8

# define STAT_FAIL					10
# define PATHNAME_DOESNT_EXIST		11
# define PATHNAME_IS_DIR			12
# define PATHNAME_ISNT_EXECUTABLE	13
# define EXEC_ISNT_IN_PATH			14
/**
 * Kinda specific case of CMD_OK.
 */
# define PATHNAME_IS_BUILTIN		15
# define CMD_OK						16

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

enum	e_stdin_redir_type
{
	file,
	heredoc,
};

enum	e_stdout_redir_type
{
	overwrite,
	append,
};

enum	e_arg_type
{
	normal_arg,
	stdin_redir_arg,
	stdout_redir_arg,
};

/**
 * ---------------------------------------------------------------------------
 * unions.
 * ---------------------------------------------------------------------------
 */
/**
 * Unused. It'd be madness to bypass Norminette if we try to use this.
 */
union	u_stdin_redir
{
	const char	*stdin_file;
	const char	*heredoc_eof;
};

/**
 * ---------------------------------------------------------------------------
 * structs.
 * ---------------------------------------------------------------------------
 */
/**
 * stdin redirection.
 * In order to bypass Norminette, $data may contain either
 * a pathname for a file, or a heredoc EOF string.
 */
typedef struct s_stdin_redir
{
	enum e_stdin_redir_type		redir_type;
	const char					*data;
	/* union u_stdin_redir		redir_data; */
}	t_stdin_redir;

/**
 * stdout redirection.
 */
typedef struct s_stdout_redir
{
	enum e_stdout_redir_type	redir_type;
	const char					*output_file;
}	t_stdout_redir;

/**
 * Parsed command.
 */
typedef struct s_exec
{
	const char	*path_to_exec;
	t_list		*args;				/* List of strings. */
	char		**args_for_execve;
	t_list		*stdin_redirs;
	t_list		*stdout_redirs;
}	t_exec;

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
 * @return	(The next token);
 * 			(NULL), if there are no more tokens.
 */
char	*ft_get_next_token(char *prompt, char **saveptr);

/**
 * Depending on the quote in $quote,
 * updates what quote we currently have open.
 * @param	quote		Quote to handle.
 * @param	quotes_type	A pointer to the current quote type.
 */
void	ft_handle_quotes(char quote, enum e_quotes_type *quotes_type);

/**
 * A modified version of ft_strtok_r(), which divides token
 * gotten from ft_get_next_token() into arguments.
 *
 * Usage is similar to ft_strtok_r(): in each subsequent call that
 * parses the same token, $token must be NULL.
 * @brief	Divides token into single arguments.
 * @warning	Dynamic memory allocaiton is used.
 * @warning	Some quotes of returned argument may be unclosed.
 * @param	token	Token to divide.
 * @param	saveptr	Where to save the current position.
 * @return	If malloc() failed somewhere, $status is set to (-1) and
 * 				$ret is set to NULL;
 * 			if $status is set to 0 and $ret is set to NULL,
 * 				then are no more arguments;
 * 			if $status is set to 0 and $ret is set to non-NULL value,
 * 				then that's the next argument.
 */
t_ret	ft_get_next_arg(char *token, char **saveptr);

/**
 * Checks if all quotes in $arg are properly closed or not.
 * @param	arg	Argument to check.
 * @return (Some non-negative value), if yes;
 * 			(-1) otherwise.
 */
int		ft_check_arg_quotes(const char *arg);

/**
 * Checks if $arg is a valid argument: if it's not NULL,
 * if all brackers are closed,
 * and if $arg contains some file in case if $arg_type != normal_arg.
 * @brief	Checks if $arg is valid, depending on $arg_type.
 * @param	arg			Argument to check.
 * @param	arg_type	Type of the argument.
 * @return (Some non-negative value), if yes;
 * 			(-1) otherwise.
 */
int		ft_check_arg(const char *arg, enum e_arg_type arg_type);

/**
 * Frees arguments for execve in t_exec
 * (transformed from $args to $args_for_execve in t_exec).
 * @param	arg_for_execve	Pointer to an array of strings,
 * 							transformed from list of arguments (strings).
 */
void	ft_free_args_for_execve(char ***arg_for_execve);

/**
 * Frees a t_stdin_redir.
 * @param	stdin_redir		Pointer to t_stdin_redir to free.
 */
void	ft_free_t_stdin_redir(t_stdin_redir *stdin_redir);

/**
 * Frees a t_stdout_redir.
 * @param	stdout_redir	Pointer to t_stdout_redir to free.
 */
void	ft_free_t_stdout_redir(t_stdout_redir *stdout_redir);

/**
 * Frees a t_exec.
 * @param	exec			Pointer to t_exec to free.
 */
void	ft_free_t_exec(t_exec *exec);

/**
 * @brief	Generates error code for $arg, depending on $arg_type.
 * @param	arg			Argument to check.
 * @param	arg_type	Type of the argument.
 * @return	(ARG_EMPTY), if $arg is empty and $arg_type is normal_arg;
 * 			(UNCLOSED_SINGLE_QUOTE), if $arg has unclosed single quotes;
 * 			(UNCLOSED_DOUBLE_QUOTES), if $arg has unclosed double quotes;
 * 			(ARG_UNFINISHED_STDIN_REDIR), if $arg_type is stdin_redir_arg
 * 				and $arg is empty;
 * 			(ARG_UNFINISHED_STDOUT_REDIR), if $arg_type is stdout_redir_arg
 * 				and $arg is empty;
 * 			(ARG_INAPPROPRIATE_STDIN_REDIR), if $arg_type != normal_arg
 * 				and $arg contains stdin redirection;
 * 			(ARG_INAPPROPRIATE_STDOUT_REDIR), if $arg_type != normal_arg
 * 				and $arg contains stdout redirection;
 * 			(ARG_OK), if no errors mentioned above were found.
 */
int		ft_gen_errcode(const char *arg, enum e_arg_type arg_type);

/**
 * Processes token gotten by ft_get_next_token() and returns
 * a raw t_exec (only one command!), in which quotes aren't expanded.
 * @brief	Extracts raw t_exec from token gotten by ft_get_next_token().
 * @warning	Dynamic memory allocaiton.
 * @param	token	Token to process.
 * @return	If malloc() failed somewhere, $status is set to (-1) and
 * 				$ret is set to NULL;
 * 			if $status is set to 0 and $ret is set to NULL,
 * 				then user's input was invalid;
 * 			if $status is set to 0 and $ret is set to non-NULL value,
 * 				then shell command's syntax was valid
 * 					(HOWEVER $path_to_exec may be empty in the returned t_exec,
 * 					in which case the command is invalid,
 * 					and also nothing else is checked at this stage,
 * 					i.e. e.g. some file to redirect stdin may be inaccessible).
 */
t_ret	ft_get_cmd_raw_quotes(char *token);

/**
 * @brief	Checks if provided $arg is a builtin.
 * @param	arg	Argument to check.
 * @return	(Some non-zero value) if it is;
 * 			(0) otherwise.
 */
int		ft_is_builtin(const char *arg);

/**
 * Checks, if provided argument exists as an executable file.
 * @param	arg	Argument to check.
 * @return	(CMD_OK), if it does;
 * 			(STAT_FAIL), if stat() call failed for some reason;
 * 			some other error otherwise.
 */
int		ft_check_pathname(const char *arg);

/**
 * Parses the command: the same command will be returned, if it's a builtin
 * or if it starts with '/' or '.' (and it exists as an executable file);
 * otherwise the first path from $PATH, that contains
 * 	the specified binary (arg), will be returned.
 * @brief	Parses the command.
 * @warning	Dynamic memory allocation is always used.
 * @param	vars	Pointer to structure containing last exit status 
 * 					and environment variables in a key-pair structure.
 * @param	arg		Argument (command) to parse.
 * @return	If ($status == PATHNAME_IS_BUILTIN || $status == CMD_OK),
 * 				then $ret will contain an executable file
 * 				(or builtin) to execute.
 * 			Otherwise $status will reflect it's error code,
 * 				and $ret will be (NULL).
 */
t_ret	ft_get_pathname_for_execve(const t_vars *vars, const char *arg);

#endif /* PARSE_H */

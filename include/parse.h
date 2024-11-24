/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:51:34 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 14:21:54 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/**
 * ---------------------------------------------------------------------------
 * enums.
 * ---------------------------------------------------------------------------
 */
enum e_quotes_type
{
	no_quotes,
	single_quote,
	double_quotes,
};

enum e_stdin_redir_type
{
	file,
	heredoc,
};

enum e_stdout_redir_type
{
	overwrite,
	append,
};

/**
 * ---------------------------------------------------------------------------
 * unions.
 * ---------------------------------------------------------------------------
 */
union u_stdin_redir
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
 * Wrapper primarily to catch malloc() fails.
 * $ret may be whatever, including e.g. ints casted to uintptr_t.
 */
typedef struct s_ret
{
	int		status;	/* -1 in case of an error. */
	void	*ret;
}	t_ret;

/**
 * A list of stdin redirections.
 */
typedef struct s_stdin_redir
{
	enum e_stdin_redir_type	redir_type;
	union u_stdin_redir		redir_data;
	struct s_stdin_redir	*next;
}	t_stdin_redir;

/**
 * A list of stdout redirections.
 */
typedef struct s_stdout_redir
{
	enum e_stdout_redir_type	redir_type;
	const char					*output_file;
	struct s_stdout_redir		*next;
}	t_stdout_redir;

/**
 * A helper list. During parsing, arguments will be saved here,
 * the final result will be then moved to $args in t_exec.
 */
typedef struct s_arg
{
	char			*arg;
	struct s_arg	*next;
}	t_arg;

/**
 * A list of parsed commands.
 */
typedef struct s_exec
{
	const char		*path_to_exec;
	t_arg			*args;
	char			**args_for_execve;
	t_stdin_redir	*stdin_redirs;
	t_stdout_redir	*stdout_redirs;
	struct s_exec	*next;
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
 * @return	The next token;
 * 			NULL if there are no more tokens.
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
 * parses the same tokem, $token must be NULL.
 * @brief	Divides token into single arguments.
 * @warning	Returned argument's quotes may not be closed.
 * @param	token	Token to divide.
 * @param	saveptr	Where to save the current position.
 * @return	Next argument;
 * 			NULL if there are no more arguments.
 */
char	*ft_get_next_arg(char *token, char **saveptr);

/**
 * Checks if all quotes in $arg are properly closed or not.
 * @param	arg	Argument to check.
 * @return	Some non-negative value, if yes;
 * 			(-1) otherwise.
 */
int		ft_check_arg_quotes(const char *arg);

/**
 * Frees a list of t_args.
 * @param	arg	Pointer to head of t_args' list.
 */
void	ft_free_t_args(t_arg **arg);

/**
 * Frees arguments for execve
 * (transformed from list of t_args to array of strings). 
 * @param	arg_for_execve	Pointer to an array of strings,
 * 							transformed from list of t_args.
 */
void	ft_free_args_for_execve(char ***arg_for_execve);

/**
 * Frees a list of t_stdin_redirs.
 * @param	stdin_redir	Pointer to head of t_stdin_redirs' list.
 */
void	ft_free_t_stdin_redirs(t_stdin_redir **stdin_redir);

/**
 * Frees a list of t_stdout_redirs.
 * @param	stdout_redir	Pointer to head of t_stdout_redirs' list.
 */
void	ft_free_t_stdout_redirs(t_stdout_redir **stdout_redir);

/**
 * Frees a list of t_execs.
 * @param	exec	Pointer to head of t_execs' list.
 */
void	ft_free_t_execs(t_exec **exec);

/**
 * Processes token gotten by ft_get_next_token() and returns raw t_exec,
 * in which quotes aren't expanded.
 * @breif	Extracts raw t_exec from token gotten by ft_get_next_token().
 * @param	token	Token to process.
 * @return	If malloc() failed somewhere, $status is set to (-1) and
 * 				$ret is set to NULL;
 * 			if $status is set to 0 and $ret is set to NULL,
 * 				then user's input was invalid;
 * 			if $status is set to 0 and $ret is set to non-NULL value,
 * 				then we have a correct executable
 * 				and shell's syntax was valid
 * 				(nothing else is checked however, i.e. e.g. some file
 * 				to redirect stdin may be inaccessible).
 */
t_ret	ft_get_cmd_raw_quotes(char *token);

#endif	/* PARSE_H */

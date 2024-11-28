/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:51:34 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/28 11:49:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include <libft.h>

/**
 * ---------------------------------------------------------------------------
 * enums.
 * ---------------------------------------------------------------------------
 */
enum e_quotes_type {
    no_quotes,
    single_quote,
    double_quotes,
};

enum e_stdin_redir_type {
    file,
    heredoc,
};

enum e_stdout_redir_type {
    overwrite,
    append,
};

/**
 * ---------------------------------------------------------------------------
 * unions.
 * ---------------------------------------------------------------------------
 */
/**
 * Unused. It'd be madness to bypass Norminette if we try to use this.
 */
union u_stdin_redir {
    const char* stdin_file;
    const char* heredoc_eof;
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
typedef struct s_ret {
    /**
     * $status values meaning:
     * 	(-1): error that should lead to exit of minishell;
     * 	Non-negative value: can proceed as normal.
     * 		Those however can be further adjusted
     * 		depending on the indivial functions.
     */
    int status;
    void* ret;
} t_ret;

/**
 * stdin redirection.
 * In order to bypass Norminette, $data may contain either
 * a pathname for a file, or a heredoc EOF string.
 */
typedef struct s_stdin_redir {
    enum e_stdin_redir_type redir_type;
    const char* data;
    /* union u_stdin_redir	redir_data; */
} t_stdin_redir;

/**
 * stdout redirection.
 */
typedef struct s_stdout_redir {
    enum e_stdout_redir_type redir_type;
    const char* output_file;
} t_stdout_redir;

/*
typedef struct s_list
{
    void						*content;
    struct s_list				*next;
}								t_list;
*/

/**
 * Parsed command.
 */
typedef struct s_exec {
    const char* path_to_exec;
    t_list* args; /* List of pointers to char (strings). */
    char** args_for_execve;
    t_list* stdin_redirs;
    t_list* stdout_redirs;
} t_exec;

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
 * @return (The next token);
 * 			NULL if there are no more tokens.
 */
char* ft_get_next_token(char* prompt, char** saveptr);

/**
 * Depending on the quote in $quote,
 * updates what quote we currently have open.
 * @param	quote		Quote to handle.
 * @param	quotes_type	A pointer to the current quote type.
 */
void ft_handle_quotes(char quote, enum e_quotes_type* quotes_type);

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
 * @return (Next argument);
 * 			NULL if there are no more arguments.
 * @return	If malloc() failed somewhere, $status is set to (-1) and
 * 				$ret is set to NULL;
 * 			if $status is set to 0 and $ret is set to NULL,
 * 				then are no more arguments;
 * 			if $status is set to 0 and $ret is set to non-NULL value,
 * 				then that's the next argument.
 */
t_ret ft_get_next_arg(char* token, char** saveptr);

/**
 * Checks if all quotes in $arg are properly closed or not.
 * @param	arg	Argument to check.
 * @return (Some non-negative value, if yes);
 * 			(-1) otherwise.
 */
int ft_check_arg_quotes(const char* arg);

/**
 * Frees arguments for execve in t_exec
 * (transformed from $args to $args_for_execve in t_exec).
 * @param	arg_for_execve	Pointer to an array of strings,
 * 							transformed from list of arguments (strings).
 */
void ft_free_args_for_execve(char*** arg_for_execve);

/**
 * Frees a t_stdin_redir.
 * @param	stdin_redir	Pointer to t_stdin_redir to free.
 */
void ft_free_t_stdin_redir(t_stdin_redir* stdin_redir);

/**
 * Frees a t_stdout_redir.
 * @param	stdout_redir	Pointer to t_stdout_redir to free.
 */
void ft_free_t_stdout_redir(t_stdout_redir* stdout_redir);

/**
 * Frees a t_exec.
 * @param	exec	Pointer to t_exec to free.
 */
void ft_free_t_exec(t_exec* exec);

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
t_ret ft_get_cmd_raw_quotes(char* token);

#endif /* PARSE_H */

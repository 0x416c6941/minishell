/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:34:55 by hlyshchu          #+#    #+#             */
/*   Updated: 2024/11/24 11:51:20 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Declare the global variable
extern int						is_interactive;

typedef struct s_exec
{
	char						*path_to_exec;
	char						**args;
	const char					*stdin_list;
	const char					*stdout_list;
	unsigned char				is_heredoc;
	// enum stdout_;
}								t_exec;

typedef struct s_info
{
	int							status;
	const char					*error_msg;
	t_exec						*cmd;
	const size_t				cmds_size;
}								t_info;

typedef struct s_stdout_file
{
	char						*output_file;
	int							append;
	t_stdout_file				*next;
}								t_stdout_file;

typedef struct s_command
{
	char						*path_to_exec;
	char **args;            // Array of arguments
	size_t arg_count;       // Number of arguments
	char *input_file;       // Input redirection file
	char **output_file;     // Output redirection filee
	int append;             // Append mode (1 if `>>`, 0 otherwise)
	struct s_command *next; // Pointer to the next command (for pipes)
}								t_command;

typedef struct s_ret_check
{
	int status; // -1 in case of an error
	void *ret;  // Obmazatsya: ukazatel na cho ugodno
}								t_ret_check;

// Function prototypes
t_ret_check						parse_input(const char *input);
void							free_command(t_command *cmd);

// Declare signal handling setup function
void							setup_signals(void);

<<<<<<< HEAD

#endif
=======
// utils.c
bool							ft_isspace(const char c);
bool							check_unclosed_quotes(const char *str);

/**
 * Wrapper primarily to catch malloc() fails.
 * ret may be whatever, including e.g. ints casted to uintptr_t.
 */
typedef struct s_ret
{
	int status; /* -1 in case of a crucial error. */
	void						*ret;
}								t_ret;

enum							e_stdin_redir_type
{
	file,
	heredoc,
};

union							u_stdin_redir
{
	const char					*stdin_file;
	const char					*heredoc_eof;
};

/**
 * A list of stdin redirections.
 */
typedef struct s_stdin_redir
{
	enum e_stdin_redir_type		redir_type;
	union u_stdin_redir			redir_data;
	t_stdin_redir				*next;
}								t_stdin_redir;

enum							e_stdout_redir_type
{
	overwrite,
	append,
};

/**
 * A list of stdout redirections.
 */
typedef struct s_stdout_redir
{
	enum e_stdout_redir_type	redir_type;
	const char					*output_file;
	t_stdout_redir				*next;
}								t_stdout_redir;

/**
 * A helper structure. During parsing, arguments will be saved here,
 * the final result will be then moved to $args in t_exec.
 */
typedef struct t_arg
{
	char						*arg;
	t_arg						*next;
}								t_arg;

/**
 * A list of parsed commands.
 */
typedef struct t_exec
{
	const char					*path_to_exec;
	char						**args;
	t_stdin_redir				*stdin_redirs;
	t_stdout_redir				*stdout_redirs;
	t_exec						*next;
}								t_exec;

#endif /* MINISHELL_H */

>>>>>>> fdc67c1 (Adding utils.c with check_unclosed_quotes and ft_isspace)

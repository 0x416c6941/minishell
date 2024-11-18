/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:34:55 by hlyshchu          #+#    #+#             */
/*   Updated: 2024/11/18 15:22:01 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <libft.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// Declare the global variable
extern int is_interactive;

typedef struct s_exec
{
	char *path_to_exec;
	char **args;
	const char *stdin_list;
	const char *stdout_list;
	unsigned char is_heredoc;
	// enum stdout_;
} t_exec;

typedef struct s_info
{
	int status;
	const char *error_msg;
	t_exec *cmd;
	const size_t cmds_size;
} t_info;

typedef struct s_stdout_file
{
	char *output_file;
	int append;
	t_stdout_file *next;
}	t_stdout_file;

typedef struct s_command
{
	char *path_to_exec;
	char **args;			// Array of arguments
	size_t arg_count;		// Number of arguments
	char *input_file;		// Input redirection file
	char **output_file;		// Output redirection filee
	int append;				// Append mode (1 if `>>`, 0 otherwise)
	struct s_command *next; // Pointer to the next command (for pipes)
} t_command;

typedef struct s_ret_check
{
	int status;	// -1 in case of an error
	void *ret;	// Obmazatsya: ukazatel na cho ugodno
}	t_ret_check;

// Function prototypes
t_ret_check parse_input(const char *input);
void free_command(t_command *cmd);

// Declare signal handling setup function
void setup_signals(void);

<<<<<<< HEAD


#endif
=======
// utils.c
bool ft_isspace(const char c);
bool check_unclosed_quotes(const char *str);





typedef struct s_ret_check
{
	int status;	// -1 in case of an error
	void *ret;	// Obmazatsya: ukazatel na cho ugodno
}	t_ret_check;

typedef struct s_stdin_file
{
	const char *stdin_file;		// If $is_heredoc isn't 0, this will be ending word for heredoc
	unsigned short is_heredoc;	// 0 - not heredoc, everything else - heredoc
	t_stdin_file *next;
}	t_stdin_file;

typedef struct s_stdout_file
{
	char *output_file;
	int append;
	t_stdout_file *next;
}	t_stdout_file;

typedef struct t_exec
{

	char *path_to_exec; //asagymba task
	char **args;
	t_stdin_file *stdin_file;
	t_stdout_file *stdout_file;	// 0 - '>'
	t_exec *next;
}	t_exec;


#endif /* MINISHELL_H */
>>>>>>> fdc67c1 (Adding utils.c with check_unclosed_quotes and ft_isspace)

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:34:55 by hlyshchu          #+#    #+#             */
/*   Updated: 2024/11/25 19:04:29 by asagymba         ###   ########.fr       */
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

// Declare signal handling setup function
void setup_signals(void);



#endif

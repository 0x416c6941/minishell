/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:06:45 by root              #+#    #+#             */
/*   Updated: 2024/11/15 11:17:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Define the global variable
int is_interactive = 0;

void handle_sigint(int sig)
{
	(void)sig;
	if (is_interactive)
	{
		// Clear current input line and redisplay prompt
		rl_replace_line("", 0);
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
	}
	else
	{
		// Non-interactive: exit with status 130
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
}

void handle_sigquit(int sig)
{
	(void)sig;
	if (is_interactive)
	{
		// Ignore `Ctrl-\` in interactive mode
		write(STDOUT_FILENO, "\b\b  \b\b", 6);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		// Non-interactive: exit with status 131
		write(STDOUT_FILENO, "Quit: 3\n", 8);
		exit(131);
	}
}

void setup_signals(void)
{
	struct sigaction sa;

	sa.sa_flags = SA_RESTART; // Restart interrupted system calls
	sigemptyset(&sa.sa_mask);

	// Handle SIGINT (Ctrl-C)
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);

	// Handle SIGQUIT (Ctrl-\)
	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}

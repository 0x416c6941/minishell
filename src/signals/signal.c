/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:57:25 by root              #+#    #+#             */
/*   Updated: 2024/12/17 20:22:16 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

static void	sig_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sig_print_newline(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

int	handle_signal_noninteractive(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sig_print_newline;
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);
	return (0);
}

int	handle_signal_interactive(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	ft_memset(&sigint, 0, sizeof(sigint));
	sigint.sa_handler = &sig_reset_prompt;
	ft_memset(&sigquit, 0, sizeof(sigquit));
	sigquit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sigint, NULL) == -1
		|| sigaction(SIGQUIT, &sigquit, NULL) == -1)
		return (-1);
	return (0);
}

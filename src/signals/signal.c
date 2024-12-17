/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:57:25 by root              #+#    #+#             */
/*   Updated: 2024/12/17 13:15:42 by hlyshchu         ###   ########.fr       */
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

static void	ignore_sigquit(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
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
	if (sigaction(SIGINT, &sa, NULL) == -1 || \
		sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);
	return (0);
}

int	handle_signal_interactive(void)
{
	struct sigaction	sa;

	ignore_sigquit();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sig_reset_prompt;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	return (0);
}

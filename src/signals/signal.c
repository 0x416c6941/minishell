/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:57:25 by root              #+#    #+#             */
/*   Updated: 2024/12/16 14:46:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

static void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

static void	signal_print_newline(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

/**
 * @brief Sets handlers for SIGINT and SIGQUIT to print a newline.
 *
 * Configures the behavior for SIGINT and SIGQUIT signals using the
 * sigaction system call. Both signals will trigger the
 * signal_print_newline function when received.
 *
 * @return int Returns 0 on success, -1 on failure.
 */
int	handle_signal_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (-1);
	return (0);
}

/**
 * @brief Sets a signal handler for SIGINT to reset the prompt.
 *
 * This function establishes a custom signal handler for the `SIGINT` signal
 * (typically triggered by `Ctrl+C`) that calls the `signal_reset_prompt`
 * function. It first ensures that the `SIGQUIT` signal is ignored by calling
 * `ignore_sigquit`.
 *
 * @return int Returns 0 on success, or -1 if setting the signal handler fails.
 */
int	handle_signal_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	if (sigaction(SIGINT, &act, NULL) == -1)
	{
		perror("sigaction SIGINT failed");
		return (-1);
	}
	return (0);
}

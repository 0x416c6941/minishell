/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:52:41 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/16 02:24:55 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * No, like really, I absolutely despise Norminette.
 * But, oh well, if we got here, then it means fork()
 * 	will be definitely required.
 * @brief	Another bypass.
 * @param	data	Minishell's data.
 * @return	(-1), if something went wrong and we should leave:
 * 			(Some non-negative value) is returned otherwise.
 */
static int	ft_execute_norminette(t_minishell_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (data->should_leave = true,
			data->with_which_code = MESSED_UP, -1);
	if (pid == 0)
		return (data->should_leave = true, ft_prep_env_and_exec(data));
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->vars.last_exit_status = WEXITSTATUS(status);
	return (0);
}

int	ft_execute(t_minishell_data *data)
{
	int		ret;
	t_exec	*cmd;

	if (ft_lstsize(data->parser_result) == 1
		&& ((t_ret *)data->parser_result->content)->status
		== PATHNAME_IS_BUILTIN)
	{
		cmd = ((t_ret *)data->parser_result->content)->ret;
		if (cmd->stdin_redir.is_initialized)
			if (dup2(cmd->stdin_redir.fd, STDIN_FILENO) == -1
				|| close(cmd->stdin_redir.fd) == -1)
				return (-1);
		if (cmd->stdout_redir.is_initialized)
			if (dup2(cmd->stdout_redir.fd, STDOUT_FILENO) == -1
				|| close(cmd->stdout_redir.fd) == -1)
				return (-1);
		ret = ft_exec_builtin(data,
				((t_ret *)data->parser_result->content)->ret);
		if (ft_restore_stdin_stdout(data) == -1)
			return (-1);
		return (ret);
	}
	return (ft_execute_norminette(data));
}

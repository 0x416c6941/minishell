/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prep_env_and_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:38:19 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/15 20:57:32 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <unistd.h>
#include <parse.h>
#include <input_validation.h>
#include <utils.h>

/**
 * Normiette Bypass. Lines 11, 13, 18 and 20 aren't good,
 * 	but I don't want to fight Norminette anymore.
 * @param	pipes	Output where to store the pipes after processing.
 * @param	pid		Where to save pid after fork().
 * @return	(-1), if something went bad;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_save_pipes_and_fork(int pipes[2], pid_t *pid)
{
	int	tmp_pipes[2];

	if (pipe(tmp_pipes) == -1)
		return (-1);
	*pid = fork();
	if (*pid == -1)
		return (-1);
	else if (*pid == 0)
	{
		if (pipes[0] != -1)
			(void)close(pipes[0]);
		pipes[0] = tmp_pipes[0];
		(void)close(tmp_pipes[1]);
	}
	else
	{
		if (pipes[1] != -1)
			(void)close(pipes[1]);
		pipes[1] = tmp_pipes[1];
		(void)close(tmp_pipes[0]);
	}
	return (0);
}

/**
 * Handles all redirections.
 * @param	data	Minishell's data.
 * @param	pipes	Pipes from ft_prep_env_and_exec()
 * 					(and ft_save_pipes_and_fork()).
 * @param	cmd_i	Index of the command to execute.
 * @return	(-1), if something went wrong;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_prep_env(t_minishell_data *data, int pipes[2], int cmd_i)
{
	t_exec	*cmd;

	if (pipes[0] != -1)
	{
		if (dup2(pipes[0], STDIN_FILENO) == -1)
			return (-1);
		(void)close(pipes[0]);
	}
	if (pipes[1] != -1)
	{
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			return (-1);
		(void)close(pipes[1]);
	}
	cmd = ((t_ret *)(ft_lstat(data->parser_result,
					(size_t)cmd_i))->content)->ret;
	if (cmd->stdin_redir.is_initialized)
		if (dup2(cmd->stdin_redir.fd, STDIN_FILENO) == -1
			|| close(cmd->stdin_redir.fd) == -1)
			return (-1);
	if (cmd->stdout_redir.is_initialized)
		if (dup2(cmd->stdout_redir.fd, STDOUT_FILENO) == -1
			|| close(cmd->stdout_redir.fd) == -1)
			return (-1);
	return (0);
}

/**
 * Final execution.
 * @param	data	Minishell's data.
 * @param	cmd_i	Index of the command to execute.
 * @return	(-1), if something went wrong;
 * 			(Some non-negative value) otherwise:
 * 				this non-negative value will be the exit code of
 * 				the program / builtin.
 */
static int	ft_exec(t_minishell_data *data, int cmd_i)
{
	t_ret	*cmd;

	cmd = ft_lstat(data->parser_result, (size_t)cmd_i)->content;
	if (cmd->status != PATHNAME_IS_BUILTIN && cmd->status != CMD_OK)
	{
		if (ft_gen_errmsg(cmd->status, ft_lstat(data->parser_result,
					(size_t)cmd_i + 1)) == -1)
			return (-1);
		return (1);
	}
	else if (cmd->status == PATHNAME_IS_BUILTIN)
		return (ft_exec_builtin(data, cmd->ret));
	if (execve(((t_exec *)cmd->ret)->path_to_exec,
			((t_exec *)cmd->ret)->args_for_execve,
			NULL) == -1)
		return (data->with_which_code = MESSED_UP, -1);
	return (-1);
}

int	ft_prep_env_and_exec(t_minishell_data *data)
{
	int		cmd_cnt;
	int		i;
	int		pipes[2];
	pid_t	pid;

	data->should_leave = true;
	cmd_cnt = ft_lstsize(data->parser_result);
	i = 0;
	pipes[0] = -1;
	pipes[1] = -1;
	while (i < cmd_cnt - 1)
	{
		if (ft_save_pipes_and_fork(pipes, &pid) == -1)
			return (data->with_which_code = MESSED_UP, -1);
		if (pid != 0)
			break ;
		i++;
	}
	if (((t_ret *)(ft_lstat(data->parser_result, (size_t)i)->content))
		->ret != NULL)
		if (ft_prep_env(data, pipes, i) == -1)
			return (data->with_which_code = MESSED_UP, -1);
	return (ft_exec(data, i));
}

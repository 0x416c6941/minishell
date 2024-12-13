/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:26:25 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/13 17:37:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <expander.h>
#include <input_validation.h>
#include <libft.h>
#include <parse.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

static void	test_builtin(t_list *cmds, t_vars *vars)
{
	t_ret	*current_node;
	t_exec	*cmd;
	int		status;

	(void)ft_printf("\n");
	(void)ft_printf("test_builtin\n");
	while (cmds != NULL)
	{
		(void)ft_printf("\n");
		// Retrieve the current command node
		current_node = cmds->content;
		cmds = cmds->next;
		// Skip if the command is not a built-in or valid
		if (current_node->status != PATHNAME_IS_BUILTIN
			&& current_node->status != CMD_OK)
			continue ;
		cmd = current_node->ret;
		// Process `echo` built-in command
		if (ft_strcmp(cmd->path_to_exec, "echo") == 0)
		{
			vars->last_exit_status = echo_builtin((const char **)(cmd->args_for_execve
						+ 1));
			printf("echo exit code: %d\n", vars->last_exit_status);
		}
		// Process `exit` built-in command
		else if (ft_strcmp(cmd->path_to_exec, "exit") == 0)
		{
			status = exit_builtin((const char **)(cmd->args_for_execve + 1),
					&vars->last_exit_status);
			// Handle fatal error in `exit_builtin`
			if (status == EXIT_FATAL_ERROR)
			{
				printf("Fatal error in exit_builtin\n");
				return ;
			}
			// Print the exit code and stop processing commands
			printf("exit_builtin exit code: %d\n", vars->last_exit_status);
			return ;
		}
		// Process `exit` built-in command
		else if (ft_strcmp(cmd->path_to_exec, "env") == 0)
		{
			vars->last_exit_status = env_builtin(vars);
			// Handle fatal error in `exit_builtin`
			if (vars->last_exit_status == EXIT_FATAL_ERROR)
			{
				printf("Fatal error in exit_builtin\n");
				return ;
			}
			// Print the exit code and stop processing commands
			printf("env exit code: %d\n", vars->last_exit_status);
			break ;
		}
		else if (ft_strcmp(cmd->path_to_exec, "pwd") == 0)
		{
			vars->last_exit_status = pwd_builtin(vars,
					(const char **)cmd->args_for_execve + 1);
			// Handle fatal error in `exit_builtin`
			if (vars->last_exit_status == EXIT_FATAL_ERROR)
			{
				printf("Fatal error in pwd_builtin\n");
				return ;
			}
			// Print the exit code and stop processing commands
			printf("pwd exit code: %d\n", vars->last_exit_status);
		}
		else if (ft_strcmp(cmd->path_to_exec, "unset") == 0)
		{
			vars->last_exit_status = unset_builtin(&vars->envs,
					(const char **)cmd->args_for_execve + 1);
			// Handle fatal error in `exit_builtin`
			if (vars->last_exit_status == EXIT_FATAL_ERROR)
			{
				printf("Fatal error in unset_builtin\n");
				return ;
			}
			// Print the exit code and stop processing commands
			printf("unset_builtin exit code: %d\n", vars->last_exit_status);
		}
	}
}

/**
 * A temporary helper function to write parsed commands.
 * @param	cmds	A list gotten by ft_final_parser().
 */
static void	ft_write_cmds_content(t_list *cmds)
{
	t_ret	*current_node;
	t_exec	*cmd;
	size_t	i;
	t_list	*j;

	while (cmds != NULL)
	{
		current_node = cmds->content;
		cmds = cmds->next;
		if (current_node->status != PATHNAME_IS_BUILTIN
			&& current_node->status != CMD_OK)
			continue ;
		(void)ft_printf("\n");
		cmd = current_node->ret;
		(void)ft_printf("path_to_exec:\n\t%s\n", cmd->path_to_exec);
		(void)ft_printf("args_for_execve:\n");
		if (cmd->args_for_execve != NULL)
		{
			i = 0;
			// echo_builtin((const char **)(cmd->args_for_execve + 1));   TEST
			while (cmd->args_for_execve[i] != NULL)
				printf("\t%s\n", (const char *)cmd->args_for_execve[i++]);
		}
		(void)ft_printf("stdin_redirs:\n");
		j = cmd->stdin_redirs;
		while (j != NULL)
		{
			if (((t_stdin_redir *)j->content)->redir_type == file)
				(void)ft_printf("\tfile, ");
			else
				(void)ft_printf("\theredoc, ");
			(void)ft_printf("%s\n", ((t_stdin_redir *)j->content)->data);
			j = j->next;
		}
		(void)ft_printf("stdout_redirs:\n");
		j = cmd->stdout_redirs;
		while (j != NULL)
		{
			if (((t_stdout_redir *)j->content)->redir_type == overwrite)
				(void)ft_printf("\toverwrite, ");
			else
				(void)ft_printf("\tappend, ");
			(void)ft_printf("%s\n",
				((t_stdout_redir *)j->content)->output_file);
			j = j->next;
		}
	}
}

#define BAD_MSG "owo s0me malloc() or I/O fa1led ;((\n"
#define MESSED_UP 1

/**
 * In case of some malloc() fail,
 * 	rl_clear_history() and ft_lstclear() aren't called.
 * But we'll fix that later.
 */
int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	t_ret	parser_status;
	int		validation_status;
	char	*input;

	(void)argc;
	(void)argv;
	vars.last_exit_status = 0;
	/* Idc it's not a parser. */
	parser_status = ft_initialize_envs((const char **)envp);
	if (parser_status.status == -1)
		return ((void)ft_errmsg(BAD_MSG), MESSED_UP);
	vars.envs = parser_status.ret;
	while (42)
	{
		input = readline("almost minishell $> ");
		if (input == NULL)
			break ;
		if (!ft_input_issspace(input))
		{
			add_history(input);
			validation_status = ft_check_unsupported(input);
			if (validation_status == -1 || validation_status == 0)
			{
				free(input);
				if (validation_status == -1)
					return (ft_errmsg(BAD_MSG), rl_clear_history(),
						ft_lstclear(&vars.envs,
							(void (*)(void *))ft_free_t_env), MESSED_UP);
				continue ;
			}
			validation_status = ft_has_invalid_pipe_position(input);
			if (validation_status == -1 || validation_status == 0)
			{
				free(input);
				if (validation_status == -1)
					return (ft_errmsg(BAD_MSG), rl_clear_history(),
						ft_lstclear(&vars.envs,
							(void (*)(void *))ft_free_t_env), MESSED_UP);
				continue ;
			}
			parser_status = ft_final_parser(&vars, input);
			if (parser_status.status == -1)
				return (ft_errmsg(BAD_MSG), rl_clear_history(),
					ft_lstclear(&vars.envs, (void (*)(void *))ft_free_t_env),
					MESSED_UP);
			validation_status = ft_are_there_syntax_errors_in_parsed_cmd(parser_status.ret);
			if (validation_status == -1)
				return (rl_clear_history(), ft_lstclear(&vars.envs,
						(void (*)(void *))ft_free_t_env),
					ft_lstclear((t_list **)&parser_status.ret,
						(void (*)(void *))ft_free_t_ret_with_t_exec),
					MESSED_UP);
			else if (validation_status > 0)
			{
				free(input);
				ft_lstclear((t_list **)&parser_status.ret,
					(void (*)(void *))ft_free_t_ret_with_t_exec);
				continue ;
			}
			if (ft_gen_errmsgs(parser_status.ret) == -1)
				return (rl_clear_history(), ft_lstclear(&vars.envs,
						(void (*)(void *))ft_free_t_env),
					ft_lstclear((t_list **)&parser_status.ret,
						(void (*)(void *))ft_free_t_ret_with_t_exec),
					MESSED_UP);
			ft_write_cmds_content(parser_status.ret);
			test_builtin(parser_status.ret, &vars);
			ft_lstclear((t_list **)&parser_status.ret,
				(void (*)(void *))ft_free_t_ret_with_t_exec);
		}
		free(input);
	}
	(void)ft_printf("exit\n");
	rl_clear_history();
	ft_lstclear(&vars.envs, (void (*)(void *))ft_free_t_env);
	return (0);
}

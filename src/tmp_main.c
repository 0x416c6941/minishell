/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:26:25 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/12 21:35:42 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <expander.h>
#include <input_validation.h>
#include <libft.h>
#include <parse.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <stdlib.h>
#include <utils.h>

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
			echo_builtin((const char **)cmd->args_for_execve);
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
			ft_lstclear((t_list **)&parser_status.ret,
				(void (*)(void *))ft_free_t_ret_with_t_exec);
		}
		free(input);
	}
	(void)ft_printf("Exit...\n");
	rl_clear_history();
	ft_lstclear(&vars.envs, (void (*)(void *))ft_free_t_env);
	return (0);
}

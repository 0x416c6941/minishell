/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:26:25 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/02 23:30:28 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <libft.h>
#include <parse.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * A temporary helper function to write the content of $cmd.
 * @param	cmd	A command to write the content of.
 */
static void	ft_write_cmd_content(t_exec *cmd)
{
	t_list	*i;
	size_t	j;

	(void)ft_printf("\n");
	if (cmd == NULL)
	{
		(void)ft_printf("Got NULL. Input was incorrent.\n");
		return ;
	}
	(void)ft_printf("args:\n");
	i = cmd->args;
	while (i != NULL)
	{
		(void)ft_printf("\t%s\n", (const char *)i->content);
		i = i->next;
	}
	(void)ft_printf("args_for_execve:\n");
	j = 0;
	if (cmd->args_for_execve != NULL)
	{
		while (cmd->args_for_execve[j])
		{
			printf("\t%s\n", (const char *)cmd->args_for_execve[j]);
			j++;
		}
	}
	(void)ft_printf("stdin_redirs:\n");
	i = cmd->stdin_redirs;
	while (i != NULL)
	{
		if (((t_stdin_redir *)i->content)->redir_type == file)
			(void)ft_printf("\tfile, ");
		else
			(void)ft_printf("\theredoc, ");
		(void)ft_printf("%s\n", ((t_stdin_redir *)i->content)->data);
		i = i->next;
	}
	(void)ft_printf("stdout_redirs:\n");
	i = cmd->stdout_redirs;
	while (i != NULL)
	{
		if (((t_stdout_redir *)i->content)->redir_type == overwrite)
			(void)ft_printf("\toverwrite, ");
		else
			(void)ft_printf("\tappend, ");
		(void)ft_printf("%s\n", ((t_stdout_redir *)i->content)->output_file);
		i = i->next;
	}
}

#define BAD_MSG "Something went really wrong.\n"
#define MESSED_UP 1

int	main(int argc, char **argv, char **envp)
{
	t_minishell_data	data;
	t_ret				status;
	char				*input;
	int					check_unsupported_status;
	char				*token;
	char				*next_token;

	(void)argc;
	(void)argv;
	status = ft_initialize_envs((const char **)envp);
	if (status.status == -1)
		return ((void)ft_errmsg(BAD_MSG), MESSED_UP);
	data.envs = status.ret;
	while (42)
	{
		input = readline("parser test> ");
		if (input == NULL)
			break ;
		if (ft_input_issspace(input))
		{
			add_history(input);
			check_unsupported_status = ft_check_unsupported(input);
			if (check_unsupported_status == -1
				|| check_unsupported_status == 0)
			{
				free(input);
				if (check_unsupported_status == -1)
					return (MESSED_UP);
				continue ;
			}
			token = ft_get_next_token(input, &next_token);
			while (token != NULL)
			{
				status = ft_get_cmd_raw_quotes(token);
				if (status.status == -1)
					return ((void)ft_errmsg(BAD_MSG), MESSED_UP);
				ft_write_cmd_content(status.ret);
				(void)ft_printf("\n");
				ft_free_t_exec(status.ret);
				token = ft_get_next_token(NULL, &next_token);
			}
		}
		free(input);
	}
	(void)ft_printf("Exit...\n");
	rl_clear_history();
	ft_lstclear(&data.envs, (void (*)(void *))ft_free_t_env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:26:25 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/29 16:03:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <libft.h>
#include <parse.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int			g_exit_code = 0;

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
	while (cmd->args_for_execve[j])
	{
		printf("\t%s\n", (const char *)cmd->args_for_execve[j]);
		j++;
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

int	main(void)
{
	char	*input;
	char	*token;
	char	*next_token;
	t_ret	status;

	while (42)
	{
		input = readline("parser test> ");
		if (input == NULL)
		{
			(void)ft_printf("Exit...\n");
			rl_clear_history();
			return (0);
		}
		if (input_issspace((const char *)input) == 0)
		{
			add_history(input);
			if (validate_input((const char *)input) == 0)
			{
				token = ft_get_next_token(input, &next_token);
				while (token != NULL)
				{
					status = ft_get_cmd_raw_quotes(token);
					if (status.status == -1)
					{
						(void)write(STDERR_FILENO, BAD_MSG, sizeof(BAD_MSG));
						return (MESSED_UP);
					}
					ft_write_cmd_content(status.ret);
					(void)ft_printf("\n");
					ft_free_t_exec(status.ret);
					token = ft_get_next_token(NULL, &next_token);
				}
			}
		}
		free(input);
	}
}

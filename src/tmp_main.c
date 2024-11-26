/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:26:25 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/26 11:39:25 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <parse.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * A temporary helper function to write the content of $cmd.
 * @param	cmd	A command to write the content of.
 */
static void	ft_write_cmd_content(t_exec *cmd)
{
	t_list	*i;

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

#define BAD_MSG		"Something went really wrong.\n"
#define MESSED_UP	1

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
			return (0);
		}
		add_history(input);
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
		free(input);
	}
}

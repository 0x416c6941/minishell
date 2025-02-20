/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_execs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:44:17 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/16 16:35:15 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <input_validation.h>
#include <utils.h>
#include <stdlib.h>
#include <parse.h>
#include <expander.h>

/**
 * I hate Norminette.
 * @param	readline_input	readline()'s input to free().
 * @param	status			(-1) will write $BAD_MSG to stderr; (0) will not.
 * @return	(-1), if ($status == (-1));
 * 			(MINISHELL_INPUT_INCORRECT) otherwise.
 */
static int	ft_get_execs_stupid_norminette_bypass(char *readline_input,
		int status)
{
	free(readline_input);
	if (status == -1)
		return (ft_errmsg(BAD_MSG), -1);
	return (MINISHELL_INPUT_INCORRECT);
}

/**
 * Another continuation of ft_get_execs().
 */
static int	ft_get_execs_handle_redirs(t_minishell_data *data)
{
	t_list	*exec;
	t_exec	*cmd;

	exec = data->parser_result;
	while (exec != NULL)
	{
		cmd = ((t_ret *)(exec->content))->ret;
		if (cmd != NULL)
		{
			if (ft_handle_redirs(cmd) == -1)
			{
				ft_free_t_exec(cmd);
				((t_ret *)(exec->content))->status = IO_FAIL;
				((t_ret *)(exec->content))->ret = NULL;
			}
		}
		exec = exec->next;
	}
	return (MINISHELL_INPUT_OK);
}

/**
 * Continuation of ft_get_execs().
 */
static int	ft_get_execs_parse_prompt(t_minishell_data *data, char *prompt)
{
	t_ret	pstatus;

	pstatus = ft_final_parser((const t_vars *)&data->vars, prompt);
	free(prompt);
	prompt = NULL;
	if (pstatus.status == -1)
		return (ft_errmsg(BAD_MSG), -1);
	data->parser_result = pstatus.ret;
	return (ft_get_execs_handle_redirs(data));
}

int	ft_get_execs(t_minishell_data *data)
{
	char	*input;
	int		status;
	t_ret	estatus;

	input = readline("minishell$ ");
	if (input == NULL)
		return (MINISHELL_INPUT_EOF);
	else if (ft_input_issspace(input))
		return (free(input), MINISHELL_INPUT_INCORRECT);
	add_history(input);
	estatus = ft_dup_arg_expanded(&data->vars, input);
	if (estatus.status == -1)
		return (ft_get_execs_stupid_norminette_bypass(input, estatus.status));
	else if (ft_input_issspace(estatus.ret))
		return (free(estatus.ret), free(input), MINISHELL_INPUT_INCORRECT);
	free(estatus.ret);
	status = ft_check_unsupported(input);
	if (status == -1 || status == 0)
		return (ft_get_execs_stupid_norminette_bypass(input, status));
	status = ft_has_invalid_pipe_position(input);
	if (status == -1 || status == 0)
		return (ft_get_execs_stupid_norminette_bypass(input, status));
	return (ft_get_execs_parse_prompt(data, input));
}

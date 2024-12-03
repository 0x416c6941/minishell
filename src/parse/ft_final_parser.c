/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_final_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:42:44 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/03 19:51:27 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <utils.h>
#include <expander.h>
#include <libft.h>
#include <stdlib.h>

/**
 * Gets the next command from the prompt and expands everything in it.
 * @param	vars	Pointer to structure containing last exit status
 * 					and environment variables in a key-pair structure.
 * @param	token	Token to process.
 * @return	If $status == (CMD_OK), then $ret will be a t_exec structure
 * 				containing parsed and expanded command;
 * 			$status otherwise contains an error code, and $ret is NULL.
 */
static t_ret	ft_get_next_cmd(const t_vars *vars, char *token)
{
	t_ret	ret;
	t_ret	status;

	ret = ft_get_cmd_raw_quotes(token);
	if (ret.status != CMD_OK)
		return (ft_free_t_exec(ret.ret), ret.ret = NULL, ret);
	ret.status = ft_expand_t_exec(vars, ret.ret);
	if (ret.status != CMD_OK)
		return (ft_free_t_exec(ret.ret), ret.ret = NULL, ret);
	status = ft_get_pathname_for_execve(vars,
			*(((t_exec *)ret.ret)->args_for_execve));
	ret.status = status.status;
	((t_exec *)ret.ret)->path_to_exec = status.ret;
	if (status.status != PATHNAME_IS_BUILTIN && status.status != CMD_OK)
	{
		ft_free_t_exec(ret.ret);
		ret.ret = NULL;
	}
	return (ret);
}

/**
 * Allocates cmd on the heap and appends it to the back of the list.
 * @warning	Dynamic memory allocation is used.
 * @param	head	Pointer to the head of the list.
 * @param	cmd		Command to append.
 * @return	(-1) if some malloc() failed;
 * 			(Some non-negative value) otherwise.
 */
static int	ft_append_cmd_to_head(t_list **head, t_ret cmd)
{
	t_ret	*cmd_on_heap;
	t_list	*new_node;

	cmd_on_heap = (t_ret *)malloc(sizeof(t_ret));
	if (cmd_on_heap == NULL)
		return (-1);
	cmd_on_heap->status = cmd.status;
	cmd_on_heap->ret = cmd.ret;
	new_node = ft_lstnew(cmd_on_heap);
	if (new_node == NULL)
		return (ft_free_t_ret_with_t_exec(cmd_on_heap), (-1));
	ft_lstadd_back(head, new_node);
	return (0);
}

t_ret	ft_final_parser(const t_vars *vars, char *prompt)
{
	char	*token;
	char	*next_token;
	t_list	*head;
	t_ret	cmd;

	head = NULL;
	token = ft_get_next_token(prompt, &next_token);
	while (token != NULL)
	{
		cmd = ft_get_next_cmd(vars, token);
		if (cmd.status == -1)
			return (ft_lstclear(&head,
					(void (*)(void *))ft_free_t_ret_with_t_exec),
				(t_ret){-1, NULL});
		if (ft_append_cmd_to_head(&head, cmd) == -1)
			return (ft_free_t_exec(cmd.ret),
				ft_lstclear(&head, (void (*)(void *))ft_free_t_ret_with_t_exec),
				(t_ret){-1, NULL});
		token = ft_get_next_token(NULL, &next_token);
	}
	return ((t_ret){0, head});
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_raw_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:40:16 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 18:02:28 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <stddef.h>

t_ret	ft_get_cmd_raw_quotes(char *token)
{
	t_exec	*raw_cmd;
	t_list	*ret;
	char	*arg;
	char	*arg_next;

	raw_cmd = ft_calloc(1, sizeof(t_exec));
	if (raw_cmd == NULL)
		return ((t_ret){(-1), NULL});
	ret = ft_lstnew(raw_cmd);
	if (ret == NULL)
		return (ft_free_t_exec(raw_cmd), (t_ret){-1, NULL});
	arg = ft_get_next_arg(token, &arg_next);
	while (arg != NULL)
	{
		if (ft_check_arg_quotes(arg) == -1)
			return (ft_lstclear(&ret, (void (*)(void *))ft_free_t_exec),
					(t_ret){-1, NULL});
		//else if (
	}
	if (raw_cmd->path_to_exec == NULL)
		return (ft_lstclear(&ret, (void (*)(void *))ft_free_t_exec),
				(t_ret){-1, NULL});
	return ((t_ret){0, ret});
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_raw_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:40:16 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 13:52:09 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <stddef.h>

t_ret	ft_get_cmd_raw_quotes(char *token)
{
	t_exec	*ret;
	char	*arg;
	char	*arg_next;

	ret = ft_calloc(1, sizeof(t_exec));
	if (ret == NULL)
		return ((t_ret){ - 1, NULL });
	arg = ft_get_next_arg(token, &arg_next);
	while (arg != NULL)
	{
		if (ft_check_arg_quotes(arg) == -1)
			return (ft_free_t_execs(&ret), (t_ret){ 0, NULL });
	}
	if (ret->path_to_exec == NULL)
		return (ft_free_t_execs(&ret), (t_ret){ 0, NULL });
	return ((t_ret){ 0, ret });
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:52:41 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/15 17:29:34 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

/**
 * No, like really, I absolutely despise Norminette.
 * But, oh well, if we got here, then it means fork()
 * 	will be definitely required.
 * @brief	Another bypass.
 * @param	data	Minishell's data.
 * @return	(-1), if something went wrong and we should leave:
 * 			(Some non-negative value) is returned otherwise.
 */
static int	ft_execute_norminette(t_minishell_data *data)
{
	// TODO
	(void)data;
	return (0);
}

int	ft_execute(t_minishell_data *data)
{
	int	ret;

	if (ft_lstsize(data->parser_result) == 1
		&& ((t_ret *)data->parser_result->content)->status
		== PATHNAME_IS_BUILTIN)
	{
		if (ft_handle_redirs(((t_ret *)data->parser_result->content)->ret)
			== -1)
		{
			if (ft_restore_stdin_stdout(data) == -1)
				return (-1);
			return (0);
		}
		ret = ft_exec_builtin(data,
				((t_ret *)data->parser_result->content)->ret);
		if (ft_restore_stdin_stdout(data) == -1)
			return (-1);
		return (ret);
	}
	return (ft_execute_norminette(data));
}

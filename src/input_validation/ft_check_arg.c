/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:21:13 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/10 11:54:33 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <stddef.h>
#include <libft.h>

int	ft_check_arg(const char *arg, enum e_arg_type arg_type)
{
	if (arg == NULL || ft_check_arg_quotes(arg) == -1
		|| (arg_type != normal_arg
			&& (ft_strcmp(arg, "<<") == 0
				|| ft_strcmp(arg, "<") == 0
				|| ft_strcmp(arg, ">>") == 0
				|| ft_strcmp(arg, ">") == 0)))
		return (-1);
	return (0);
}

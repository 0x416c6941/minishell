/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_export_arg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:07:18 by root              #+#    #+#             */
/*   Updated: 2024/12/15 14:21:46 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input_validation.h>
#include <libft.h>
#include <stdbool.h>

bool	ft_is_valid_export_arg(const char *arg)
{
	if (*arg != '_' && !ft_isalpha(*arg))
		return (false);
	arg++;
	while (*arg != '\0' && *arg != '=')
	{
		if (*arg != '_' && !ft_isalnum(*arg))
			return (false);
		arg++;
	}
	return (true);
}

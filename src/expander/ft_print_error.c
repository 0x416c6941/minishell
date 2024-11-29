/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:57:47 by root              #+#    #+#             */
/*   Updated: 2024/11/29 15:59:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

void	ft_print_error(const char *error_message)
{
	if (error_message == NULL)
		return ;
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
}

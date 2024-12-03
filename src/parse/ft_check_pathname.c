/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pathname.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:38:46 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/03 14:42:04 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <sys/stat.h>
#include <unistd.h>

int	ft_check_pathname(const char *arg)
{
	struct stat	statbuf;

	if (access(arg, F_OK) == -1)
		return (PATHNAME_DOESNT_EXIST);
	else if (stat(arg, &statbuf) == -1)
		return (STAT_FAIL);
	else if (S_ISDIR(statbuf.st_mode))
		return (PATHNAME_IS_DIR);
	else if (access(arg, X_OK) == -1)
		return (PATHNAME_ISNT_EXECUTABLE);
	return (PATHNAME_OK);
}

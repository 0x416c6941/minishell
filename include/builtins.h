/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:24:29 by root              #+#    #+#             */
/*   Updated: 2024/12/13 16:03:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <libft.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <utils.h>

/*
To be consistent with t_ret in case of success will be exot code positive (1)
and in case of failure will be negative (-1).
*/
# define EXIT_OK 1
# define EXIT_FATAL_ERROR -1

int	echo_builtin(const char *args[]);
int	env_builtin(t_vars *vars);
int	export_no_args_builtin(t_vars *vars);
int	exit_builtin(const char *args[], int *last_exit_code);

#endif /* BUILTINS_H */
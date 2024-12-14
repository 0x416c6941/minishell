/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:24:29 by root              #+#    #+#             */
/*   Updated: 2024/12/14 19:28:18 by asagymba         ###   ########.fr       */
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

/**
 * To be consistent with t_ret, in case of success
 * 	exit code will be positive (1)
 * and in case of failure will be negative (-1).
 */
# define EXIT_OK 1
# define EXIT_FATAL_ERROR -1

int			echo_builtin(const char *args[]);
int			env_builtin(t_vars *vars);
int			export_builtin(t_list **env_head, const char **args);
int			exit_builtin(const char *args[], int *last_exit_code);
const char	*parse_sign_and_skip_whitespace(const char *nptr, int *sign);
int			pwd_builtin(t_vars *vars, const char **args);
int			unset_builtin(t_list **envs, const char **args);

#endif /* BUILTINS_H */

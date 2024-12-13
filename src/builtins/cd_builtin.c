/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:18:41 by root              #+#    #+#             */
/*   Updated: 2024/12/13 17:01:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

/* update_wds:
 *	Updates the PWD and OLDPWD in the environment after a directory change.
 *	A copy of the paths are stored internally for use in case the environment
 *	variables are unset.
 */
static void	update_wds(t_data *data, char *wd)
{
	set_env_var(data, "OLDPWD", get_env_var_value(data->env, "PWD"));
	set_env_var(data, "PWD", wd);
	if (data->old_working_dir)
	{
		free_ptr(data->old_working_dir);
		data->old_working_dir = ft_strdup(data->working_dir);
	}
	if (data->working_dir)
	{
		free_ptr(data->working_dir);
		data->working_dir = ft_strdup(wd);
	}
	free_ptr(wd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_t_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:56:15 by asagymba          #+#    #+#             */
/*   Updated: 2024/12/02 23:20:10 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <stddef.h>
#include <stdlib.h>

void	ft_free_t_env(t_env *env)
{
	if (env == NULL)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

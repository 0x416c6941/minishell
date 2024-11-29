/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:28:06 by root              #+#    #+#             */
/*   Updated: 2024/11/29 14:25:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <parse.h>
# include <stdlib.h>

t_ret	*ft_process_args(const char *content);
int		expand_var(char *str);
#endif /* EXPANDER_H */
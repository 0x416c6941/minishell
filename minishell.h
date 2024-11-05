/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:34:55 by hlyshchu          #+#    #+#             */
/*   Updated: 2024/11/05 15:51:03 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_info
{
    t_builtin_ptr   builtins[7];
    char            reserved_words[7];
    char **envp;
    t_llist     envp_list;
    bool        envp_f; //flag: need to update  envp_list (if no operation envp_list was executed -> no need to update)
    bool        exit_f; //flag: to exit -> need to free resources
    int         status; // need to handle $? (advantage: no need to be a global var)
    //all commands executed in subprocess except builtins
    
} t_info;



#endif
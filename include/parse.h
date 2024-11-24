/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:51:34 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 11:53:27 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/**
 * ---------------------------------------------------------------------------
 * Structures, unions and enums.
 * ---------------------------------------------------------------------------
 */
/**
 * Wrapper primarily to catch malloc() fails.
 * ret may be whatever, including e.g. ints casted to uintptr_t.
 */
typedef struct s_ret
{
	int		status;	/* -1 in case of a crucial error. */
	void	*ret;
}	t_ret;

enum e_stdin_redir_type
{
	file,
	heredoc,
};

union u_stdin_redir
{
	const char	*stdin_file;
	const char	*heredoc_eof;
};

/**
 * A list of stdin redirections.
 */
typedef struct s_stdin_redir
{
	enum e_stdin_redir_type	redir_type;
	union u_stdin_redir		redir_data;
	t_stdin_redir			*next;
}	t_stdin_redir;

enum e_stdout_redir_type
{
	overwrite,
	append,
};

/**
 * A list of stdout redirections.
 */
typedef struct s_stdout_redir
{
	enum e_stdout_redir_type	redir_type;
	const char					*output_file;
	t_stdout_redir				*next;
}	t_stdout_redir;

/**
 * A helper structure. During parsing, arguments will be saved here,
 * the final result will be then moved to $args in t_exec.
 */
typedef struct t_arg
{
	char	*arg;
	t_arg	*next;
}	t_arg;

/**
 * A list of parsed commands.
 */
typedef struct t_exec
{
	const char		*path_to_exec;
	char			**args;
	t_stdin_redir	*stdin_redirs;
	t_stdout_redir	*stdout_redirs;
	t_exec			*next;
}	t_exec;

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */

#endif	/* PARSE_H */

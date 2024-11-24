/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:51:34 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/24 12:28:13 by asagymba         ###   ########.fr       */
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
	struct t_stdin_redir	*next;
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
	struct t_stdout_redir		*next;
}	t_stdout_redir;

/**
 * A list of parsed commands.
 */
typedef struct t_exec
{
	const char		*path_to_exec;
	char			**args;
	t_stdin_redir	*stdin_redirs;
	t_stdout_redir	*stdout_redirs;
	struct t_exec	*next;
}	t_exec;

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * A modified version of ft_strtok_r(), which tokenizes prompt
 * by '|' delimiters and doesn't clear consecutive delimiters.
 *
 * Usage is similar to ft_strtok_r(): in each subsequent call that
 * parses the same prompt, $prompt must be NULL.
 * @brief	Tokenizes prompt by '|' delimiters.
 * @param	prompt	The string to tokenize.
 * @param	saveptr	Where to save the current position.
 * @return	The next token;
 * 			NULL if there are no more tokens.
 */
char	*ft_get_next_token(char *prompt, char **saveptr);

#endif	/* PARSE_H */

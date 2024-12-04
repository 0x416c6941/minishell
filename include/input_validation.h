/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:35:47 by root              #+#    #+#             */
/*   Updated: 2024/12/04 19:35:10 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_VALIDATION_H
# define INPUT_VALIDATION_H

# include <libft.h>

/**
 * ---------------------------------------------------------------------------
 * Constants.
 * ---------------------------------------------------------------------------
 */
# define ERR_UNSUPPORTED				"||, &, &&, ; and \\ are unsuppowwted\n"
# define ERR_PIPE_START					"owo... unexpected token '|' :(((\n"
# define ERR_PIPE_END					"UwU got unexpected EOF (newline) :(((\n"
# define UNCLOSED_SINGLE_QUOTE_ERR		"some ' isn't cl0sed :c\n"
# define UNCLOSED_DOUBLE_QUOTES_ERR		"some \" isn't closed x_x\n"
# define UNFINISHED_REDIR_ERR			"some red1rection is unfinished ._.\n"
# define INAPPROPRIATE_STDIN_REDIR_ERR	"unexp3cted < or <<\n"
# define INAPPROPRIATE_STDOUT_REDIR_ERR	"unexp3cted > or >>\n"
# define AMBIGIOUS_REDIR_ERR			"ambigi0us red1rection :3\n"
# define STAT_FAIL_ERR					"stat()-san failed\n"
# define PATHNAME_DOESNT_EXIST_ERR		"some pathname doesn't exist\n"
# define PATHNAME_IS_DIR_ERR			"some pathname is a directory\n"
# define PATHNAME_ISNT_EXECUTABLE_ERR	"can't exec some pathname\n"
# define EXEC_ISNT_IN_PATH_ERR			"some pathname isn't in $PATH\n"

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * Checks if $str contains any of the unsupported characters:
 * 	||, &, &&, ; and \.
 * If it does, then error message is also generated to stderr by using
 * ft_errmsg().
 * @brief	Check for unsupported characters and generate error message
 * 			if any is found.
 * @param	str	The string to check.
 * @return	(Some positive value), if no unsupported characters are found;
 * 			(0), if unsupported characters and error message was successfully
 * 				written to stderr;
 * 			(-1), if write to stderr has failed.
 */
int	ft_check_unsupported(const char *str);

/**
 * Check for invalid pipe positions in the beginning or in the end of $str.
 * @param	str	String to check.
 * @return	(-1) if found invalid pipe and write to stderr failed;
 * 			(0) if found some invalid pipe and wrote log to stderr;
 * 			(Some positive value) otherwise;
 */
int	ft_has_invalid_pipe_position(const char *str);

/**
 * Checks, if in a list of parsed commands, gotten by ft_final_parser(),
 * at least one command wasn't entered correctly by user.
 * @brief	Check if there are no mistakes in what user entered.
 * @param	parsed_cmd	Head of a list of parsed commands
 * 						gotten by ft_final_parser().
 * @return	(0), if there are no mistakes;
 * 			(some other value) otherwise.
 */
int	ft_are_there_mistakes_in_parsed_cmd(const t_list *parsed_cmd);

/**
 * For every command in a list of parsed commands, gotten by ft_final_parser(),
 * writes an error message to stderr, if there are any mistakes.
 * @param	parsed_cmd	Head of a list of parsed commands
 * 						gotten by ft_final_parser().
 * @return	(-1), if some write() to stderr failed;
 * 			(some non-negative value) if everything went ok.
 */
int	ft_gen_errmsgs(const t_list *parsed_cmd);

#endif /* INPUT_VALIDATION_H */

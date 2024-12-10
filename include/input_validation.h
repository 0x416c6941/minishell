/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:35:47 by root              #+#    #+#             */
/*   Updated: 2024/12/10 12:01:56 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_VALIDATION_H
# define INPUT_VALIDATION_H

# include <libft.h>
# include <parse.h>

/**
 * ---------------------------------------------------------------------------
 * Constants.
 * ---------------------------------------------------------------------------
 */
# define ERR_UNSUPPORTED				"||, &, &&, ; and \\ are unsuppowwted\n"
# define ERR_PIPE_START					"owo... unexpected token '|' :(((\n"
# define ERR_PIPE_END					"UwU got unexpected EOF (newline) :((\n"
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
 * Checks if all quotes in $arg are properly closed or not.
 * @param	arg	Argument to check.
 * @return (Some non-negative value), if yes;
 * 			(-1) otherwise.
 */
int	ft_check_arg_quotes(const char *arg);

/**
 * Checks if $arg is a valid argument: if it's not NULL,
 * if all brackers are closed,
 * and if $arg contains some file in case if $arg_type != normal_arg.
 * @brief	Checks if $arg is valid, depending on $arg_type.
 * @param	arg			Argument to check.
 * @param	arg_type	Type of the argument.
 * @return (Some non-negative value), if yes;
 * 			(-1) otherwise.
 */
int	ft_check_arg(const char *arg, enum e_arg_type arg_type);

/**
 * Checks if $args, $stdin_redirs and $stdout_redirs are all NULL in $raw_cmd.
 * @brief	Dirty Norminette bypass.
 * @param	raw_cmd	Raw t_exec to check.
 * @return	(-1), if they are;
 * 			(some non-negative value) otherwise.
 */
int	ft_check_emptiness_raw(const t_exec *raw_cmd);

/**
 * Checks, if provided argument exists as an executable file.
 * @param	arg	Argument to check.
 * @return	(CMD_OK), if it does;
 * 			(STAT_FAIL), if stat() call failed for some reason;
 * 			some other error otherwise.
 */
int	ft_check_pathname(const char *arg);

/**
 * Generates raw error code for $arg, depending on $arg_type.
 * Please note, that only basic checks are performed here.
 * @brief	Generates error code for $arg, depending on $arg_type.
 * @param	arg			Argument to check.
 * @param	arg_type	Type of the argument.
 * @return	(ARG_EMPTY), if $arg is empty and $arg_type is normal_arg;
 * 			(UNCLOSED_SINGLE_QUOTE), if $arg has unclosed single quotes;
 * 			(UNCLOSED_DOUBLE_QUOTES), if $arg has unclosed double quotes;
 * 			(ARG_UNFINISHED_STDIN_REDIR), if $arg_type is stdin_redir_arg
 * 				and $arg is empty;
 * 			(ARG_UNFINISHED_STDOUT_REDIR), if $arg_type is stdout_redir_arg
 * 				and $arg is empty;
 * 			(ARG_INAPPROPRIATE_STDIN_REDIR), if $arg_type != normal_arg
 * 				and $arg contains stdin redirection;
 * 			(ARG_INAPPROPRIATE_STDOUT_REDIR), if $arg_type != normal_arg
 * 				and $arg contains stdout redirection;
 * 			(ARG_OK), if no errors mentioned above were found.
 */
int	ft_gen_raw_errcode(const char *arg, enum e_arg_type arg_type);

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

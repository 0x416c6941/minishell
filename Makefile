# Compiler options.
CC = cc
CFLAGS = -I$(INC_DIR) -lreadline							\
		 -Wall -Wextra -Wsign-conversion -pedantic -Werror	\
		 -g -fsanitize=address -fsanitize=bounds-strict

# Headers.
INC_DIR = include

# Source files.
SRC_DIR = src
SRC_FILES = main.c															\
			utils/ft_skip_spaces.c											\
			utils/ft_handle_quotes.c										\
			utils/ft_errmsg.c												\
			utils/ft_input_issspace.c										\
			utils/ft_free_t_env.c											\
			utils/ft_initialize_one_env.c									\
			utils/ft_initialize_envs.c										\
			utils/ft_find_env.c												\
			parse/ft_get_next_token.c										\
			parse/ft_get_next_arg.c											\
			parse/ft_free_args_for_execve.c									\
			parse/ft_free_t_stdin_redir.c									\
			parse/ft_free_t_stdout_redir.c									\
			parse/ft_free_t_exec.c											\
			parse/ft_get_cmd_raw_quotes.c									\
			parse/ft_is_builtin.c											\
			parse/ft_get_pathname_for_execve.c								\
			parse/ft_free_t_ret_with_t_exec.c								\
			parse/ft_final_parser.c											\
			expander/ft_get_env_value.c										\
			expander/ft_extract_var_name.c									\
			expander/ft_calculate_expanded_arg_size.c						\
			expander/ft_dup_arg_expanded.c									\
			expander/ft_is_whole_arg_var.c									\
			expander/ft_expand_t_exec.c										\
			expander/ft_expand_heredoc_delim.c								\
			expander/ft_handle_heredoc.c									\
			input_validation/ft_check_unsupported.c							\
			input_validation/ft_has_invalid_pipe_position.c					\
			input_validation/ft_check_arg_quotes.c							\
			input_validation/ft_check_arg.c									\
			input_validation/ft_check_pathname.c							\
			input_validation/ft_check_emptiness_raw.c 						\
			input_validation/ft_gen_raw_errcode.c							\
			input_validation/ft_are_there_syntax_errors_in_parsed_cmd.c		\
			input_validation/ft_gen_errmsg.c								\
			input_validation/ft_gen_errmsgs.c								\
			input_validation/ft_is_valid_export_identifier.c				\
			builtins/echo_builtin.c											\
			builtins/export_builtin.c										\
			builtins/env_builtin.c											\
			minishell/ft_init_data.c										\
			minishell/ft_free_data.c										\
			minishell/minishell.c											\
			minishell/ft_get_execs.c										\
			minishell/ft_check_syntax_and_execute.c							\
			minishell/ft_execute.c											\
			minishell/ft_handle_redirs.c									\
			minishell/ft_restore_stdin_stdout.c								\
			minishell/ft_exec_builtin.c										\
			#builtins/exit_builtin.c										\
			builtins/exit_utils.c											\
			builtins/pwd_builtin.c											\
			builtins/unset_builtin.c										\

SRC_FILES := $(addprefix $(SRC_DIR)/,$(SRC_FILES))

# Object files.
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Name of the resulting binary file.
NAME = minishell

# For other Makefiles.
EXTERNAL_DIR = external
MAKE = make

# Libft.
LIBFT_DIR = $(EXTERNAL_DIR)/Libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)/$(LIBFT_NAME)
LIBFT_CLEAN = fclean

# Targets.
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ -L$(LIBFT_DIR) -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)			# Create the $(OBJ_DIR) if it doesn't exist.
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) $(LIBFT_NAME)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) $(LIBFT_CLEAN)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

# Compiler options.
CC = cc
CFLAGS = -I$(INC_DIR) -lreadline							\
		 -Wall -Wextra -Wsign-conversion -pedantic -Werror	\
		 -g -fsanitize=address -fsanitize=bounds-strict

# Headers.
INC_DIR = include

# Source files.
SRC_DIR = src
SRC_FILES = tmp_main.c utils/ft_skip_spaces.c utils/ft_errmsg.c				\
			utils/ft_input_issspace.c utils/ft_free_t_env.c					\
			utils/ft_initialize_envs.c parse/ft_get_next_token.c			\
			parse/ft_handle_quotes.c parse/ft_get_next_arg.c				\
			parse/ft_check_arg_quotes.c parse/ft_check_arg.c				\
			parse/ft_free_args_for_execve.c parse/ft_free_t_stdin_redir.c	\
			parse/ft_free_t_stdout_redir.c parse/ft_free_t_exec.c			\
			parse/ft_gen_raw_errcode.c parse/ft_get_cmd_raw_quotes.c		\
			parse/ft_is_builtin.c parse/ft_check_pathname.c					\
			parse/ft_get_pathname_for_execve.c								\
			parse/ft_free_t_ret_with_t_exec.c								\
			parse/ft_check_emptiness_raw.c parse/ft_final_parser.c			\
			parse/ft_are_there_mistakes_in_prompt.c parse/ft_gen_errmsgs.c	\
			expander/ft_get_env_value.c expander/ft_extract_var_name.c		\
			expander/ft_calculate_expanded_arg_size.c						\
			expander/ft_dup_arg_expanded.c expander/ft_is_whole_arg_var.c	\
			expander/ft_expand_t_exec.c										\
			input_validation/ft_check_unsupported.c

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

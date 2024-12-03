# Compiler options.
CC = cc
CFLAGS = -I$(INC_DIR) -lreadline							\
		 -Wall -Wextra -Wsign-conversion -pedantic -Werror	\
		 -g -fsanitize=address

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
			parse/ft_gen_errcode.c parse/ft_get_cmd_raw_quotes.c			\
			parse/ft_is_builtin.c expander/ft_extract_var_name.c			\
			input_validation/ft_check_unsupported.c
# parse/ft_get_pathname_for_execve.c

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

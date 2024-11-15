# Compiler options.
CC = cc
CFLAGS = -Wall -Wextra -Wsign-conversion -Werror -lreadline -pedantic 			\
		 -I$(HEADS_DIR) -I$(LIBFT_HEAD_DIR) -g -fsanitize=address

# Source files
SRC_FILES = main.c signal_handle.c parse.c

# Headers directories.
HEADS_DIR = ./
LIBFT_HEAD_DIR = Libft/

# Object files.
OBJ_FILES = $(patsubst %.c,%.o,$(SRC_FILES))

# Name of the resulting binary file.
NAME = minishell

# For other Makefiles.
MAKE = make

# Libft.
LIBFT_DIR = Libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_BUILD_TARGET = all
LIBFT_CLEAN = fclean

# Targets.
all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ -L$(LIBFT_DIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR) $(LIBFT_BUILD_TARGET)

.PHONY: clean
clean:
	rm -f $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_DIR) $(LIBFT_CLEAN)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

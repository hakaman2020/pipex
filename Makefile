# defautl config
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

# Project info
NAME = pipex

# source code
SRC_DIR = src
SRC_FILES= $(addprefix $(SRC_DIR)/,\
	pipex.c \
	commands.c \
	errors.c \
	path_locator_utils.c)

# object code
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIB_DIR = lib
LIB_FLAGS = $(LIBFT_FLAGS)

# Libft library
LIBFT_DIR = libft
LIBFT_FLAGS = -L$(LIB_DIR)/$(LIBFT_DIR) -lft

all:$(NAME)

$(NAME): $(OBJ_FILES)
	$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(LIB_FLAGS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ./$(LIB_DIR)/$(LIBFT_DIR) clean
	rm -f $(OBJ_FILES)

fclean: clean
	$(MAKE) -C ./$(LIB_DIR)/$(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 

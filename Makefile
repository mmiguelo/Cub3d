#==============================================================================#
#                                    NAMES                                     #
#==============================================================================#

CC = cc
FLAGS = -g -Wall -Wextra -Werror
INC = -I./includes
RM = rm -rf

VAL = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-for-leak-kinds=definite

GENERAL = main.c utils.c
PARSING = parsing.c

NAME = cub3D

#==============================================================================#
#                                    EXTRA                                     #
#==============================================================================#

ECHO = @echo
GREEN = \033[1;32m
RED = \033[1;31m
RESET = \033[0m

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

# src
VPATH += src
# parsing
VPATH += src/parse

#==============================================================================#
#                                    FILES                                     #
#==============================================================================#

SRC +=	$(GENERAL)
SRC +=	$(PARSING)

# Library Paths
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Objects Paths
OBJ_DIR = obj
OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@$(ECHO) "$(GREEN)----------------- cub3D created$(RESET)"

# Make and run
r: all
	./cub3D

# Make and run with valgrind
rv: all
	$(VAL) ./cub3D

# Executable minishell with valgrind
v: re
	$(VAL) ./cub3D

valgrind: re
	@valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all ./$(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)----------------- OBJECTS deleted$(RESET)"

fclean: clean
	$(RM) $(NAME) $(OBJ_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)----------------- cub3D deleted$(RESET)"

re: fclean all

# Phony Targets
.PHONY: all clean fclean re
#==============================================================================#
#                                    NAMES                                     #
#==============================================================================#

CC = cc
FLAGS = -g -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -lm -lXext -lX11 -lXrandr -lXcursor -lXinerama -lXrender
INC = -I./includes -I./minilibx-linux
RM = rm -rf

VAL = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-for-leak-kinds=definite

GENERAL = main.c utils.c
PARSING = 01_parse.c 02_extensions.c 03_textures.c 04_color.c 05_map.c 06_map_utils.c
INIT	= data.c
DEBUG = print.c
MINIMAP = minimap_init.c minimap_utils.c
MAP = map.c
GAME = close_window.c keypress_handler.c

NAME = cub3D

#==============================================================================#
#                                    EXTRA                                     #
#==============================================================================#

ECHO = @echo
GREEN = \033[1;32m
RED = \033[1;31m
CYAN = \033[0;36m
MAGENTA = \033[0;35m
YELLOW  = \033[1;33m
RESET = \033[0m

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

# src
VPATH += src
# parsing
VPATH += src/parse
# init
VPATH += src/init
# debug
VPATH += src/debug
# minimap
VPATH += src/minimap
#game
VPATH += src/game
VPATH += src/map

#==============================================================================#
#                                    FILES                                     #
#==============================================================================#

SRC +=	$(GENERAL)
SRC +=	$(PARSING)
SRC +=	$(INIT)
SRC +=	$(DEBUG)
SRC +=	$(MINIMAP)
SRC +=	$(GAME)
SRC += 	$(MAP)

# Library Paths
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Objects Paths
OBJ_DIR = obj
OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Minilibx Path
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

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

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -L$(MLX_DIR) $(MLX_FLAGS) -o $(NAME)
	@echo "$(CYAN)  ______   __     __  _______    ______   _______  $(RESET)"
	@echo "$(CYAN) / _____\ | _\   | _\| ______\  / _____\ | _____ \ $(RESET)"
	@echo "$(CYAN)| /######\| ##|  | ##| #######\| /######\| #######\$(RESET)"
	@echo "$(CYAN)| ##   \##| ##|  | ##| ##__/ ## \##__| ##| ##  | ##$(RESET)"
	@echo "$(CYAN)| ##      | ##|  | ##| ##___ ##  | ___ ##| ##  | ##$(RESET)"
	@echo "$(CYAN)| ##   __ | ##|  | ##| #######\ __\#####\| ##  | ##$(RESET)"
	@echo "$(CYAN)| ##__/  \| ##|__/ ##| ##__/ ##| _\__| ##| ##__/ ##$(RESET)"
	@echo "$(CYAN) \##____## \##|____##| ##___ ## \##____##| ##__  ##$(RESET)"
	@echo "$(CYAN)  \######   \######   \#######   \######  \####### $(RESET)"
	@echo "\n"
	@echo "$(GREEN)[OK] Cub3d built$(RESET)"
	@echo "$(YELLOW)This $(NAME) was created by mmiguelo and frbranda!$(RESET)"
	@echo "--------"
	@echo "$(CYAN)Usage:$(RESET)"
	@echo "./cub3d $(YELLOW)[name_of_map_file].cub$(RESET)"
	@echo "--------"

# Make and run
r: all
	./$(NAME)

# Make and run with valgrind
rv: all
	$(VAL) ./$(NAME) 

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	@if [-d "minilibx-linux" ]; then \
		$(MAKE) clean -C $(MLX_DIR); \
	fi
	@echo "$(RED)----------------- OBJECTS deleted$(RESET)"

fclean: clean
	$(RM) $(NAME) $(OBJ_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@if [-d "minilibx-linux" ]; then \
		$(MAKE) clean -C $(MLX_DIR); \
	fi
	@echo "$(RED)----------------- cub3D deleted$(RESET)"

download:
	@if [ ! -d "minilibx-linux" ]; then \
		wget https://cdn.intra.42.fr/document/document/36093/minilibx-linux.tgz && \
		tar -xzf minilibx-linux.tgz; \
		rm -rf minilibx-linux.tgz; \
		echo "$(GREEN)MinilibX cloned into ./minilibx-linux$(RESET)"; \
	else \
		echo "$(YELLOW)MinilibX already exists at ./minilibx-linux$(RESET)"; \
	fi

re: fclean all

# Phony Targets
.PHONY: all clean fclean re r rv v download
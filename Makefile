#==============================================================================#
#                                    NAMES                                     #
#==============================================================================#

CC = cc
FLAGS = -g -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -lm -lXext -lX11 -lXrandr -lXcursor -lXinerama -lXrender
INC = -I./includes -I./minilibx-linux
BONUS_INC = $(INC)
RM = rm -rf

VAL = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-for-leak-kinds=definite

GENERAL = 	main.c \
			free.c
PARSING = 	01_parse.c \
			02_extensions.c \
			03_textures.c \
			04_color.c \
			05_map.c \
			06_map_utils.c
INIT	= 	data.c
DEBUG 	=	 print.c
GAME 	= 	close_window.c \
			game_loop.c \
			keypress_handler.c \
			player.c \
			raycasting.c \
			render.c
GENERAL_BONUS	=	main_bonus.c \
					free_bonus.c \
					cycle_bonus.c
PARSING_BONUS	= 	01_parse_bonus.c \
					02_extensions_bonus.c \
					03_textures_bonus.c \
					04_color_bonus.c \
					05_map_bonus.c \
					06_map_utils_bonus.c
INIT_BONUS		= 	data_bonus.c \
					data_util_bonus.c
DEBUG_BONUS		= 	print_bonus.c
GAME_BONUS		= 	close_window_bonus.c \
					game_loop_bonus.c \
					keypress_handler_bonus.c \
					player_move_bonus.c \
					raycasting_bonus.c \
					render_bonus.c \
					light_bonus.c \
					render_utils_bonus.c
MINIMAP_BONUS	= 	minimap_bonus.c \
					minimap_utils_bonus.c
FPS_BONUS		=	fps_bonus.c

NAME 		= cub3D
NAME_BONUS 	= cub3D_bonus

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

VPATH += src
VPATH += src/parse
VPATH += src/init
VPATH += src/debug
VPATH += src/game
VPATH += src_bonus
VPATH += src_bonus/parse_bonus
VPATH += src_bonus/init_bonus
VPATH += src_bonus/debug_bonus
VPATH += src_bonus/game_bonus
VPATH += src_bonus/minimap_bonus
VPATH += src_bonus/fps_bonus

#==============================================================================#
#                                    FILES                                     #
#==============================================================================#

SRC +=	$(GENERAL)
SRC +=	$(PARSING)
SRC +=	$(INIT)
SRC +=	$(DEBUG)
SRC +=	$(GAME)

SRC_BONUS += $(GENERAL_BONUS)
SRC_BONUS += $(PARSING_BONUS)
SRC_BONUS += $(INIT_BONUS)
SRC_BONUS += $(DEBUG_BONUS)
SRC_BONUS += $(GAME_BONUS)
SRC_BONUS += $(MINIMAP_BONUS)
SRC_BONUS += $(FPS_BONUS)

# Library Paths
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Objects Paths
OBJ_DIR = obj
OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)

# Minilibx Path
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

#mandatory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

#bonus
$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ $(BONUS_INC)

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

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX)
	$(CC) $(FLAGS) $(OBJS_BONUS) $(LIBFT) -L$(MLX_DIR) $(MLX_FLAGS) -o $(NAME_BONUS)
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
	@echo "$(GREEN)[OK] Cub3d Bonus built$(RESET)"
	@echo "$(YELLOW)This $(NAME_BONUS) was created by mmiguelo and frbranda!$(RESET)"
	@echo "--------"
	@echo "$(CYAN)Usage:$(RESET)"
	@echo "./cub3d_bonus $(YELLOW)[name_of_map_file].cub$(RESET)"
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

clean_bonus:
	$(RM) $(OBJS_BONUS)
	$(MAKE) clean -C $(LIBFT_DIR)
	@if [-d "minilibx-linux" ]; then \
		$(MAKE) clean -C $(MLX_DIR); \
	fi
	@echo "$(RED)----------------- BONUS OBJECTS deleted$(RESET)"

fclean: clean clean_bonus
	$(RM) $(NAME) $(OBJ_DIR)
	$(RM) $(NAME_BONUS) $(OBJ_DIR)
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
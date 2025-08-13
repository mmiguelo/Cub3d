/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:01:30 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/13 14:24:49 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h> // read write close
# include <stdlib.h> // malloc free exit
# include <sys/time.h> // for gettimeofday() used in frame timing
# include <string.h>
# include <stdbool.h> // true/false
# include <errno.h> // error codes
# include <fcntl.h> // for O_DIRECTORY
# include <math.h> // math trig fuctions like sin(),cos(),sqrt(),floor(),ceil()?
# include <X11/X.h>
# include <X11/keysym.h> // key press number?
# include <../minilibx-linux/mlx.h> // MinilibX (minilibx-linux.tgz needed)
# include "../libft/libft.h"
# include "ray.h"
# include "draw.h"

/*=============================================================================#
#                                   DEFINES                                    #
#=============================================================================*/

# define RST	"\033[0m"		// reset color
# define RED	"\033[1;31m"	// bold red
# define G		"\033[1;32m"	// bold green
# define Y		"\033[1;33m"	// bold yellow
# define B		"\033[1;34m"	// bold blue
# define M		"\033[1;35m"	// bold magenta
# define C		"\033[1;36m"	// bold cyan
# define W		"\033[1;37m"	// bold white

# define MAX_RGB 255
# define MIN_RGB 0

# define TILE_SIZE 64
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define PI 3.1415926535
# define FOV 66
# define FOV_RAD 1.1519173063162575
# define PLANE_LEN 0.7673269879789604
# define MOVE_SPEED 0.015
# define ROT_SPEED 0.03
# define PLAYER_RAD 0.2
# define PITCH 0

# define VALID_MAP_CHARS "01NSWE"
# define WS " \t\n\r\v\f"

# define ERR_EMPTY "File is empty\n"
# define ERR_ARGS "Arguments are invalid\n"
# define ERR_NAME "File must be *.cub\n"
# define ERR_EXTENSION_FILE "Extension must be .cub\n"
# define ERR_EXTENSION_TEXTURE "Extension must be .xpm\n"
# define ERR_FILE "File is invalid or no permissions\n"
# define ERR_MAP "Map is invalid\n"
# define ERR_PLAYER "Map must have a player\n"
# define ERR_DIRECTORY "Map sent is a directory\n"
# define ERR_MALLOC "Malloc failed\n"
# define ERR_COLOR "Color is invalid\n"
# define ERR_COLOR_RANGE "Color has invalid range\n"
# define ERR_COLOR_MISSING "Missing color value\n"
# define ERR_COLOR_MORE "RGB has more than 3 values\n"
# define ERR_TEXTURE "Texture is invalid\n"
# define ERR_TEXTURE_MISSING "Texture path is missing\n"
# define ERR_MLX "MLX failed\n"
# define ERR_ORDER "Order is invalid OR Missing Color/Texture\n"
# define ERR_DUPLICATION "Duplication found\n"
# define GAME_ENDED "Game Ended\n"
# define ERR_MLX_INIT "MLX failed to initialize\n"
# define ERR_MLX_WIN "MLX failed to open window\n"
# define ERR_TEX_LOAD "Failed to load image/texture\n"

/*=============================================================================#
#                                   STRUCTS                                    #
#=============================================================================*/

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	char	*path;
}	t_img;

typedef struct s_textures
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
}	t_textures;

typedef struct s_pair
{
	double	x;
	double	y;
}	t_pair;

typedef struct s_player
{
	char	direction;
	double	x;
	double	y;
	double	new_x;
	double	new_y;
	t_pair	dir; // x direction vector// y direction vector
	t_pair	plane; // 2d raycaster version of camera plane
	int		move_forward;
	int		move_backward;
	int		move_left;
	int		move_right;
	int		turn_left;
	int		turn_right;
}	t_player;

typedef struct s_map
{
	char		direction;
	bool		started;
	bool		ended;
	char		**grid;
	int			width;
	int			height;
}	t_map;

typedef struct s_frames
{
	double	time;
	double	old_time;
	double	frame_time; // fps / tick / delta (might or not use in the future)
}	t_frames;

typedef struct s_data
{
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
	t_map		map;
	t_frames	frames;
	double		move_speed;
	void		*mlx;
	void		*win;
	t_img		bg;
	t_img		image;
}	t_data;

/*=============================================================================#
#                                   FUNCTIONS                                  #
#=============================================================================*/

// ERROR HANDLING / CLEAN UP
int		ft_kill(t_data *data, char *message);
void	close_window(t_data *data, char *msg);
void	free_textures(t_data *data);
void	freedom(t_data *data);
void	destroy_textures(t_textures *textures, void *mlx);
void	free_tex(t_img *tex, void *mlx);

// PARSING / INITIALIZATION
void	parse(t_data *data, char *filename, char *extension);
void	parse_line(t_data *data, char *line);
void	parse_file_content(t_data *data, char *filename);
void	process_line(t_data *data, char *line, int *i);
void	check_extension(t_data *data, char *filename, char *extension);
void	check_directory(t_data *data, char *filename);
void	check_map(t_data *data, t_map	*map, char *line, int height);
void	init(t_data *data);
void	init_game(t_data *data);
void	init_image(t_data *data);
void	init_textures(t_data *data);
void	load_textures(t_data *data, t_img *texture);
void	check_textures(t_data *data, char *line);
void	assign_texture(t_data *data, char **path, char *line, int *i);
void	assign_rgb(t_data *data, t_color *color, char *line);
void	parse_color(t_data *data, t_color *color);
int		is_all_assets(t_data *data);
void	check_duplicated_color(t_data *data, t_color *ceiling, t_color *floor);
void	check_required_textures(t_data *data, t_textures textures);

// MAP UTILITIES
int		count_width(const char *str);
void	append_map_line(t_data *data, char ***grid, char *line, int height);
int		empty_line(char *line);
char	*clean_ws(t_data *data, char *line);
void	check_map_walls_and_player(t_data *data, t_map *map);
void	check_surroundings(t_data *data, char **grid, int x, int y);
bool	is_valid_map_line(char *line);
bool	is_already_rgb(t_color *color);

// DEBUG / PRINT
// TODO: delete in the end
void	print_assets(t_data *data, char *process);
void	print_map(t_data *data);
void	print_parsing_map(t_data *data, int y);

// GAME LOOP / INPUT
void	game_loop(t_data *data);
int		draw_loop(void *param);
int		x_press(t_data *data);
int		key_hook_press(int keycode, t_data *data);
int		key_hook_release(int keycode, t_data *data);

// PLAYER MOVEMENT
void	calculate_movements(t_player *player, char **map);
void	move_strafe(t_player *player, char **map);
void	turn_player(t_player *player);
void	calculate_rotation(t_player *player, double rotation_speed);
void	check_collision(t_player *player, char **map);

// PLAYER VECTOR
void	get_player_vector(t_data *data);
void	get_player_vector2(t_data *data);

// RAYCASTING / RENDERING
void	calculate_raycasting(t_data *data);
void	put_fc(t_data *data);
void	calculate_variables(t_player *player, t_ray *ray, int x);
void	calculate_variables2(t_ray *ray, double player_x, double player_y);
void	check_hit(t_data *data, t_ray *ray);
void	calculate_perpwalldist(t_ray *ray, t_draw *draw);
void	calculate_texture(t_data *data, t_ray *ray);
void	render_texture(t_ray *ray);
void	draw_line(t_data *data, t_ray *ray, int x);
int		color(t_draw *draw, t_img *texture);
void	put_pixel(t_img *img, int x, int y, int color);

#endif
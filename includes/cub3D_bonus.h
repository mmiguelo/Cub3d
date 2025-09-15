/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:01:30 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/09/15 19:42:37 by frbranda         ###   ########.fr       */
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
# include <X11/Xlib.h>
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
# define VALID_MAP_CHARS "01NSWEDdn"
# define WS " \t\n\r\v\f"

//	GAME OPTIONS:
# define TILE_SIZE 64
# define WIN_WIDTH 960 //1024
# define WIN_HEIGHT 540 //768
# define PI 3.14159265358979323846
# define FOV 66
// indoors (1) / outdoors (0)
# define INDOOR 1
// default (0.5) between -1.0 and 1.0 (only indoors wllas not implemented)
# define P_HEIGHT 0.5
# define INTERACT_RANGE 0.1

# define FOV_RAD FOV * PI / 180.0
# define PLANE_LEN tan(FOV_RAD / 2.0);
//# define FOV_RAD 1.1519173063162575
//# define PLANE_LEN 0.7673269879789604
# define SPEED 0.015
# define ROT_SPEED 0.05
# define PLAYER_RAD 0.1
# define DARKNESS 0.12
# define DAY_NIGHT_CYCLE 0.0002
# define MORNING 0x87CEEB
# define NOON    0xFFFFE0
# define EVENING 0xFCAF45
# define NIGHT   0x14183C
# define IGNORE 0xFF00FD
# define BG 0x00e5ff
# define FPS_HISTORY_SIZE 30
# define MAX_DOORS 10
# define DOOR_FPS 10.0

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

// TODO: things to add on the long run

# define NIGHT_END 0.5
# define DAY_CLUE "At dawn's first golden ray, the hidden key may stay"
# define NIGHT_CLUE "Where the last light fades, your path awaits"
# define MAP_CLUE "In the heart of the maze, where walls conceal, the truth\
 will reveal."

// Bonus Textures Path
# define IMG_BONUS "textures/bonus/"
# define IMG_CELING "./textures/bonus/ceiling/ceiling.xpm"
# define IMG_LIGHTS "./textures/bonus/ceiling/ligths.xpm"
# define IMG_FLOOR "./textures/bonus/floor/floor.xpm"

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
	int		bpp;
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
	t_img	ceiling;
	t_img	floor;
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
	int		look_up;
	int		look_down;
	int		sprint;
	double	height; // look up and down
}	t_player;

typedef enum e_door_mode
{
	DOOR_ALWAYS,
	DOOR_DAY,
	DOOR_NIGHT
}	t_door_mode;

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}	t_door_state;

typedef struct s_door
{
	int				x;
	int				y;
	t_door_mode		mode;
	t_door_state	state;
	int				frame;
	double			timer;
	int				row;
	int				col;
	char			tile;
	int				active;
}	t_door;

typedef struct s_map
{
	char		direction;
	bool		started;
	bool		ended;
	char		**grid;
	int			width;
	int			height;
	t_door		doors[MAX_DOORS];
	int			door_count;
}	t_map;

typedef struct s_frames
{
	double	time;
	double	old_time;
	double	delta_time;
	double	fps;
	double	fps_history[FPS_HISTORY_SIZE];
	int		fps_index;
	double	next_frame;
}	t_frames;

typedef struct s_minimap
{
	double		tile_size;
	double		radius;
	int		floor_color;
	int		wall_color;
	int		player_color;
	int		door_color;
	double		size;
	double		center_x;
	double		center_y;
	double	angle;
	double	cos_a;
	double	sin_a;
	double		start_tile_x;
	double		start_tile_y;
	double		radius_px;
	double		map_x;
	double		map_y;
	double		screen_x;
	double		screen_y;
	double		dist_sq;
}	t_minimap;

typedef struct s_fl
{
	//double	intensity;
	t_pair	position;
	int		flicker_frames;
	double	flicker_factor;
	double	dist;
	double	radius;
	double	factor;
}	t_fl;

typedef struct s_data
{
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
	t_fl		fl;
	t_map		map;
	t_img		image;
	t_img		fps;
	t_img		sun;
	t_img		sunrise;
	t_img		sunset;
	t_img		moon;
	t_img		door_spritesheet;
	t_frames	frames;
	t_minimap	minimap;
	bool		bsun;
	bool		bmoon;
	bool		bsunrise;
	bool		bsunset;
	bool		fl_on;
	double		time_of_day;
	double		global_light;
	double		move_speed;
	double		tmp_wall_dist;
	void		*mlx;
	void		*win;
	int			fd;
	char		*line;
	double		fov_rad; // move somewhere?
	double		plane_len; // move somewhere?
	t_ray		ray;
}	t_data;

/*=============================================================================#
#                                   FUNCTIONS                                  #
#=============================================================================*/

// ERROR HANDLING / CLEAN UP
int				ft_kill(t_data *data, char *message);
void			close_window(t_data *data, char *msg);
void			free_textures(t_data *data);
void			freedom(t_data *data);
void			destroy_images(t_data *data);
void			destroy_textures(t_textures *textures, void *mlx);
void			free_tex(t_img *tex, void *mlx);
void			free_gnl(t_data *data);

// PARSING / INITIALIZATION
void			parse(t_data *data, char *filename, char *extension);
void			parse_line(t_data *data, char *line);
void			parse_file_content(t_data *data, char *filename);
void			process_line(t_data *data, char *line, int *i);
void			check_extension(t_data *data, char *filename, char *extension);
void			check_directory(t_data *data, char *filename);
void			check_map(t_data *data, t_map	*map, char *line, int height);
void			init(t_data *data);
void			init_game(t_data *data);
void			init_image(t_data *data);
void			init_cycle_images(t_data *data);
void			init_textures(t_data *data);
void			load_textures(t_data *data, t_img *texture);
void			check_textures(t_data *data, char *line);
void			assign_texture(t_data *data, char **path, char *line, int *i);
void			assign_rgb(t_data *data, t_color *color, char *line);
void			parse_color(t_data *data, t_color *color);
int				is_all_assets(t_data *data);
void			check_duplicated_color(t_data *data,
					t_color *ceiling, t_color *floor);
void			check_required_textures(t_data *data, t_textures textures);

// MAP UTILITIES
int				count_width(const char *str);
void			append_map_line(t_data *data,
					char ***grid, char *line, int height);
int				empty_line(char *line);
char			*clean_ws(t_data *data, char *line);
void			check_map_walls_and_player(t_data *data, t_map *map);
void			check_surroundings(t_data *data, char **grid, int x, int y);
bool			is_valid_map_line(char *line);
bool			is_already_rgb(t_color *color);

// DEBUG / PRINT
// TODO: delete in the end
void			print_assets(t_data *data, char *process);
void			print_map(t_data *data);
void			print_parsing_map(t_data *data, int y);

// GAME LOOP / INPUT
void			game_loop(t_data *data);
int				draw_loop(void *param);
int				x_press(t_data *data);
int				key_hook_press(int keycode, t_data *data);
int				key_hook_release(int keycode, t_data *data);
int				mouse_move(int x, int y, t_data *data);
//void	center_mouse(void *win);

// PLAYER MOVEMENT
void			calculate_movements(t_data *data);
void			move_strafe(t_data *data);
void			turn_player(t_player *player);
void			calculate_rotation(t_player *player, double rotation_speed);
void			check_collision(t_data *data, t_player *player);

// PLAYER VECTOR
void			get_player_vector(t_data *data);
void			get_player_vector2(t_data *data);

// RAYCASTING / RENDERING
void			render_frame(t_data *data);
void			put_fc(t_data *data);
void			calculate_variables(t_player *player, t_ray *ray, int x);
void			calculate_variables2(t_ray *ray, double player_x,
					double player_y);
void			handle_wall_or_door(t_data *data, t_ray *ray);
void			apply_lighting(t_data *data, t_ray *ray, int x);
void			check_hit(t_data *data, t_ray *ray);
void			calculate_perpwalldist(t_ray *ray, t_draw *draw);
void			calculate_texture(t_data *data, t_ray *ray);
void			render_texture(t_ray *ray);
void			render_column(t_data *data, int x);
void			draw_line(t_data *data, t_ray *ray, int x);
int				color(t_draw *draw, t_img *texture);
void			draw_pixel(t_img *img, int x, int y, int color);

// LIGHT MANIPULATION
int				apply_brightness(int color, double brightness);
int				apply_global_brightness(int color, double global_light);
void			update_global_light(t_data *data);
void			update_time_of_day(t_data *data);
int				lerp_day_cycle(t_data *data, double day_cycle);
int				lerp_color(int start, int end, double t);
void			change_day(bool *to_false, bool *to_true);
void			render_cycle(t_data *data);

// MINIMAP
void			draw_minimap_tile(t_data *data, int screen_x, int screen_y,
					int color);
void			init_minimap(t_data *data);
void			render_minimap(t_data *data, t_minimap *minimap);
void			draw_minimap_player(t_data *data);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			clear_image(t_img *img, int color);
void			calc_minimap_transform(t_data *data, t_minimap *m);
int				minimap_tile_screen(t_minimap *minimap, int px, int py);

// FPS
void			init_fps(t_data *data);
double			get_current_time_in_miliseconds(void);
void			update_fps(t_data *data);
void			render_fps(t_data *data);

//door
void			parse_door(t_data *data, int x, int y);
void			sample_door_texture(t_data *data, t_ray *ray, t_door *door);
void			mark_door_hit(t_data *data, t_ray *ray);
void			animate_door_frame(t_data *data, t_door *door,
					t_door_state new_state);
int				is_door_active(t_data *data, t_door *door);
t_door			*get_door_at_tile(t_map *map, int x, int y);
t_door			*find_nearby_door(t_data *data, double px,
					double py, double max_dist);
void			update_all_doors(t_data *data);
void			toggle_door_state(t_data *data);
void			update_door_frame(t_door *door);

void			render_wall_texture(t_data *data, t_ray *ray);

// floor and ceiling (indoor)
void			render_fc(t_data *data, t_fccast *fc);
int				player_inside_door(t_data *data, t_door *door);
void			render_fc_pixel(t_data *data, t_fccast *fc, t_img *texture);

// flashlight
unsigned int	get_pixel(t_img *img, int x, int y);
void			draw_flashlight_overlay(t_data *data);
void			toggle_flashlight(t_data *data);
void			apply_flashlight_pixel(t_data *data,
					t_fl *flashlight, int x, int y);
void			update_flicker(t_data *data);

#endif

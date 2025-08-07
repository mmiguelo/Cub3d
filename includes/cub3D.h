#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h> // read write close
# include <stdlib.h> // malloc free exit
# include <sys/time.h> // for gettimeofday() used in frame timing
# include <string.h>
# include <stdbool.h> // true/false
# include <errno.h> // error codes
# include <fcntl.h> // for O_DIRECTORY
# include <math.h> // math trig fuctions like sin(),cos(),sqrt(),floor(),ceil()?
# include <X11/keysym.h> // key press number?
# include <../minilibx-linux/mlx.h> // MinilibX (minilibx-linux.tgz needed)
# include <mlx_int.h> // internal mlx functions (use with caution)
# include "../libft/libft.h"

/*=============================================================================#
#                                   DEFINES                                    #
#=============================================================================*/

/*
** ANSI color codes for terminal output
** Usage:
** 		printf(RED "This text is red" RST);
** 		printf(G "This text is green" RST);
** Remember to reset the color after using it with RST.
*/
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

# define NORTH	1
# define SOUTH	2
# define WEST	3
# define EAST	4

# define TILE_SIZE 64
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define PI 3.1415926535
# define FOV 66
# define FOV_RAD (POV * PI / 180)
# define PLANE_LEN TAN(FOV_RAD / 2)
// #define FOV 1.1519173063 in case we need

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
# define ERR_MLX "MLX failed\n"
# define ERR_MLX_INIT "MLX failed to initialize\n"
# define ERR_MLX_WIN "MLX failed to open window\n"
# define ERR_TEX_LOAD "Failed to load image/texture\n"

/*=============================================================================#
#                                   STRUCTS                                    #
#=============================================================================*/

typedef struct s_minimap
{
	void	*floor;
	void	*wall;
	void	*player;
	int		tile_size;
}	t_minimap;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/**
 * @brief Image metadata used for raw pixel manipulation in MiniLibX
 * 
 * @param path to the XPM file.
 * @param img MLX image object created by mlx_new_image()
 * @param addr raw memory address of image pixels 
 * 	(returned by mlx_get_data_addr)
 * @param bits_per_pixel Number of bits used to represent one pixel
 * 	(32 = ARGB, 64 = ARGB with extended precision)
 * @param line_length number bites of one line/row of pixels
 * @param endian Byte order-> 0 = little_endian (BGRA) | 1 = big_endian (ARGB)
 * @param width Width of the image in pixels
 * @param height Height of the image in pixels
 */
typedef struct s_tex
{
	char	*path;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_tex;

/* typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img_data;

typedef struct s_texture
{
	char		*path; // north.path == NULL
	t_img_data	img;
}	t_texture; */

typedef struct s_txt
{
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
}	t_txt;

typedef struct s_textures
{
	t_tex	north;
	t_tex	south;
	t_tex	east;
	t_tex	west;
}	t_textures;

typedef struct s_pair{
	double x;
	double y;
}	t_pair;

typedef struct s_player
{
	double	x; //position vector of the player
	double	y;
	char	direction; // 'N' 'S' 'E' 'W'
	t_pair	dir; // x direction vector// y direction vector
	t_pair	plane; // 2d raycaster version of camera plane
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
	t_textures	textures; //memset
	t_color		floor;
	t_color		ceiling;
	t_player	player;
	t_map		map;
	t_frames	frames;
	double		move_speed;
	void		*mlx;
	void		*win;
	t_txt		txt; // mlx textures
	t_minimap	minimap; //variavles for minimap
}	t_data;

/*=============================================================================#
#                                   FUNCTIONS                                  #
#=============================================================================*/

int		ft_kill(t_data *data, char *message);
void	parse(t_data *data, char *filename, char *extension);
void	parse_file_content(t_data *data, char *filename);
void	process_line(t_data *data, char *line, int *i);
void	check_extension(t_data *data, char *filename, char *extension);
void	check_directory(t_data *data, char *filename);
void	check_map(t_data *data, t_map	*map, char *line, int height);
void	init(t_data *data);
void	check_textures(t_data *data, char *line);
void	assign_texture(t_data *data, char **path, char *line, int *i);
void	assign_rgb(t_data *data, t_color *color, char *line);
void	parse_color(t_data *data, t_color *color);
int		is_all_assets(t_data *data);
void	check_duplicated_color(t_data *data, t_color *ceiling, t_color *floor);
void	check_required_textures(t_data *data, t_textures textures);
void	free_textures(t_data *data);
void	freedom(t_data *data);
int		count_width(const char *str);
void	append_map_line(t_data *data, char ***grid, char *line, int height);
int		empty_line(char *line);
char	*clean_ws(t_data *data, char *line);
void	check_map_walls_and_player(t_data *data, t_map *map);
void	check_surroundings(t_data *data, char **grid, int x, int y);
bool	is_valid_map_line(char *line);
bool	is_already_rgb(t_color *color);
void	parse_line(t_data *data, char *line);

// TODO: delete in the end
void	print_assets(t_data *data, char *process);
void	print_map(t_data *data);
void	print_parsing_map(t_data *data, int y);

// minimap
void	create_minimap(t_data *data);
void	init_minimap(t_data *data);
void	load_textures(t_data *data);
void	calculate_tile_size(t_data *data);
void	fill_image_with_color(void *img, int tile_size, int color);

int		close_window(t_data *data, char *msg);
int		x_press(t_data *data);
void	move_up(t_data *data);
void	move_down(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
int		keypress_handler(int keycode, t_data *data);
void	destroy_textures(t_textures *textures, void *mlx);
void	free_tex(t_tex *tex, void *mlx);
void	render_image(t_data *data, char c, int x, int y);
void	render_minimap(t_data *data);
int		game_loop(t_data *data);

#endif

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
# include <../minilibx-linux/mlx.h> // MinilibX (minilibx-linux.tgz needed)
//# include <mlx_int.h> // internal mlx functions (use with caution)
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

# define NORTH	1
# define SOUTH	2
# define WEST	3
# define EAST	4

typedef enum e_error_code
{
	ERR_ARGS,
	ERR_NAME,
	ERR_EXTENSION,
	ERR_FILE,
	ERR_MAP,
	ERR_DIRECTORY,
	ERR_MALLOC,
	ERR_COLOR,
	ERR_TEXTURE,
	ERR_MLX,
	ERR_ORDER,
	ERR_DUPLICATION,
}			t_error_code;

/*=============================================================================#
#                                   STRUCTS                                    #
#=============================================================================*/

/**
 * Colors:
 * r - red
 * g - green
 * b - blue
 */
typedef struct s_color
{
	int	r; // change to float  maybe
	int	g;
	int	b;
}	t_color;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*sky;
}				t_textures;

typedef struct s_player
{
	double	x;
	double	y;
	char	direction; // 'N' 'S' 'E' 'W' <- maybe this is better
	//int	direction; // NORTH SOUTH EAST WEST (escolher)
}	t_player;


typedef struct s_img_data
{
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img_data;

typedef struct s_data
{
	char		**grid;
	int			x;
	int			y;
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
	t_img_data	img_data;
	void		*mlx;
	void		*win;
}	t_data;

/*=============================================================================#
#                                   FUNCTIONS                                  #
#=============================================================================*/

int			ft_kill(t_data *data, t_error_code code);
void		check_extension(char *filename);
void		check_directory(char *filename);
void		parse(char *filename);
const char	*message(t_error_code i);

#endif
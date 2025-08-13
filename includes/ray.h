#ifndef RAY_H
# define RAY_H

# include "draw.h"

typedef struct s_camera
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	screen_x;
}	t_camera;

typedef struct s_ray_dir
{
	double	x;
	double	y;
}	t_ray_dir;

typedef struct s_ray_pos
{
	int	x;
	int	y;
}	t_ray_pos;

typedef struct s_ray_step
{
	int		x;
	int		y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
}			t_ray_step;

typedef struct s_ray
{
	t_camera	cam;
	t_ray_dir	dir;
	t_ray_pos	pos;
	t_ray_step	step;
	t_draw		draw;
}	t_ray;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:01:22 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/09/12 13:49:28 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_fccast
{
	double		x;	// world X coordinate
	double		y;	// world Y coordinate
	t_ray_dir	dir0;	// direction of the leftmost ray
	t_ray_dir	dir1;	// direction of the rightmost ray
	t_ray_dir	step;	// increments per pixel
	double		pos_z;	// center of the screen
	int			horizon; // camera/player height (default 0.5)
	double		row_distance;	// distance to current row
	int			dist_limit; // (optional limiting ceiling and floor render)
	t_ray_pos	cell;	// (cell_x, cell_y) world grid cell
	t_ray_dir	tex;	// (tex_x, tex_y) texture coordinate
	t_ray_pos	temp;	//temp for norminette handling
}	t_fccast;

typedef struct s_ray
{
	t_camera	cam;
	t_ray_dir	dir;
	t_ray_pos	pos;
	t_ray_step	step;
	t_draw		draw;
	t_fccast	fc;
}	t_ray;

#endif
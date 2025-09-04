/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:01:22 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/09/04 18:41:59 by frbranda         ###   ########.fr       */
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

typedef struct s_floorcast
{
	double		x;	// world X coordinate
	double		y;	// world Y coordinate
	t_ray_dir	dir0;	// direction of the leftmost ray
	t_ray_dir	dir1;	// direction of the rightmost ray
	t_ray_step	step;	// step in world X and y per screen pixel
	double		pos_z;		// camera height (usually 0.5 of height)
	double		row_distance;	// distance to current row
}	t_floorcast;

typedef struct s_ray
{
	t_camera	cam;
	t_ray_dir	dir;
	t_ray_pos	pos;
	t_ray_step	step;
	t_draw		draw;
	t_floorcast	floor;
}	t_ray;


#endif
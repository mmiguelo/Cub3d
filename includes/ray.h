#ifndef RAY_H
# define RAY_H

# include "draw.h"

/**
 * @brief Ray direction & projection plane used for raycasting
 *
 * @param dir_x X-component of the player's view direction vector
 * @param dir_y Y-component of the player's view direction vector
 * @param plane_x X-component of the camera plane (perpendicular to dir)
 * @param plane_y Y-component of the camera plane
 * @param screen_x Current column position in camera space [-1, 1]
 */
typedef struct s_camera
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	screen_x;
}	t_camera;

/**
 * @brief Ray direction vector for a single screen column
 * 
 * This vector represents the exact direction the ray is cast toward 
 * for a given vertical stripe (`x`) on the screen. It is calculated 
 * per frame, per column, based on the player's view direction and 
 * camera plane (FOV).
 * 
 * @param x X-component of the ray direction
 * @param y Y-component of the ray direction
 */
typedef struct s_ray_dir
{
	double	x;
	double	y;
}	t_ray_dir;

/**
 * @brief Integer coordinates of the player's position in the map grid
 * 
 * @param x Current horizontal map cell/grid
 * @param y Current vertical map cell/grid
 */
typedef struct s_ray_pos
{
	int	x;
	int	y;
}	t_ray_pos;

/**
 * @brief Raycasting step and distance calculations
 * 
 * @param x Step direction in X axis (-1 or 1)
 * @param y Step direction in Y axis (-1 or 1)
 * @param side_dist_x Distance from current position to next X side
 * @param side_dist_y Distance from current position to next Y side
 * @param delta_dist_x Ray length to move 1 unit in X direction
 * @param delta_dist_y Ray length to move 1 unit in Y direction
 */
typedef struct s_ray_step
{
	int	x;
	int	y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
}	t_ray_step;

/**
 * @brief Full container for all raycasting state per column
 * 
 * @param cam Ray direction and camera plane
 * @param pos Integer grid position in map
 * @param step Step logic and distances
 * @param draw Drawing info for vertical slice
 */
typedef struct s_ray
{
	t_camera	cam;
	t_ray_dir	dir;
	t_ray_pos	pos;
	t_ray_step	step;
	t_draw		draw;
}	t_ray;

/*=============================================================================#
#                                   FUNCTIONS                                  #
#=============================================================================*/

#endif
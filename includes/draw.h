#ifndef DRAW_H
# define DRAW_H

/**
 * @brief Draw info calculated after DDA hit
 * 
 * @param perp_wall_dist Corrected distance to wall
 * @param line_height Height of vertical line to draw
 * @param draw_start Y-start pixel of the line to draw
 * @param draw_end Y-end pixel of the line to draw
 * @param side Side of the wall hit (0: X side/wall, 1: Y side/wall)
 * @param hit Was a wall hit?
 */
typedef struct s_draw
{
	void	*texture; //to store current texture to render
	double	perpWallDist;
	int		line_height;
	int		start;
	int		end;
	int		side;
	bool	hit;
	int		texNum;
	int		pitch;
	double	wallX;
	int		texX;
	int		texY;
	double	texPos;
	double	step;
	unsigned int	color;
}	t_draw;

/*=============================================================================#
#                                   FUNCTIONS                                  #
#=============================================================================*/

#endif
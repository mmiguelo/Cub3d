#ifndef DRAW_H
# define DRAW_H

typedef struct s_draw
{
	void	*texture; //to store current texture to render
	double	perpwalldist;
	int		line_height;
	int		start;
	int		end;
	int		side;
	bool	hit;
	int		texnum;
	int		pitch;
	double	wallx;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
	int		color;
}	t_draw;

/*=============================================================================#
#                                   FUNCTIONS                                  #
#=============================================================================*/

#endif
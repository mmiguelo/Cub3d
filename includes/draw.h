/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:01:26 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/30 23:30:17 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	double	brightness;
	char	tile;
}	t_draw;

/*=============================================================================#
#                                   FUNCTIONS                                  #
#=============================================================================*/

#endif
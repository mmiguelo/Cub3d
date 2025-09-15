/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:28:44 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/16 01:28:44 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	minimap_tile_screen(t_minimap *minimap, int px, int py)
{
	int	dx;
	int	dy;

	dx = px - minimap->radius;
	dy = py - minimap->radius;
	minimap->screen_x = minimap->center_x + (int)(((dx + 0.5) * minimap->cos_a
				- (dy + 0.5) * minimap->sin_a) * minimap->tile_size);
	minimap->screen_y = minimap->center_y + (int)(((dx + 0.5) * minimap->sin_a
				+ (dy + 0.5) * minimap->cos_a) * minimap->tile_size);
	minimap->dist_sq = (minimap->screen_x - minimap->center_x)
		* (minimap->screen_x - minimap->center_x)
		+ (minimap->screen_y - minimap->center_y)
		* (minimap->screen_y - minimap->center_y);
	return (minimap->dist_sq <= minimap->radius_px * minimap->radius_px);
}

void	init_minimap(t_data *data)
{
	data->minimap.tile_size = 6;
	data->minimap.radius = 8;
	data->minimap.floor_color = 0x222222;
	data->minimap.wall_color = 0xFFFFFF;
	data->minimap.player_color = 0x00FF00;
	data->minimap.door_color = 0xFF0000;
	data->minimap.size = data->minimap.tile_size
		* (data->minimap.radius * 2 + 1);
}

void	calc_minimap_transform(t_data *data, t_minimap *m)
{
	m->center_x = m->size / 2;
	m->center_y = m->size / 2;
	m->angle = atan2(data->player.dir.y, data->player.dir.x);
	m->cos_a = cos(m->angle + PI / 2);
	m->sin_a = sin(m->angle - PI / 2);
	m->start_tile_x = (int)data->player.x - m->radius;
	m->start_tile_y = (int)data->player.y - m->radius;
	m->radius_px = m->radius * m->tile_size;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_img *img, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			my_mlx_pixel_put(img, x, y, color);
	}
}

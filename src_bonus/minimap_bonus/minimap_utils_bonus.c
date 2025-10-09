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

void	init_minimap(t_data *data)
{
	data->minimap.tile_size = 6;
	data->minimap.radius = 14;
	data->minimap.floor_color = 0x222222;
	data->minimap.wall_color = 0xFFFFFF;
	data->minimap.player_color = 0x00FF00;
	data->minimap.door_color = 0xFF0000;
	data->minimap.size = data->minimap.tile_size
		* (data->minimap.radius * 2 + 1);
	init_img(&data->minimap.minimap_map, data->mlx, data->map.width
		* data->minimap.tile_size, data->map.height * data->minimap.tile_size);
	paint_in_ignore(&data->minimap.minimap_map, IGNORE);
}

void	calc_minimap_transform(t_data *data, t_minimap *m)
{
	m->center_x = m->size / 2;
	m->center_y = m->size / 2;
	m->angle = atan2(data->player.dir.y, data->player.dir.x);
	m->cos_a = cos(m->angle + PI / 2);
	m->sin_a = sin(m->angle + PI / 2);
	m->start_tile_x = data->player.x - m->radius;
	m->start_tile_y = data->player.y - m->radius;
	m->radius_px = m->radius * m->tile_size;
}

void	render_full_minimap_map(t_data *data)
{
	t_minimap	*m;
	int			y;
	int			x;
	int			py;
	int			px;

	m = &data->minimap;
	y = -1;
	while (++y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			py = -1;
			while (++py < m->tile_size)
			{
				px = -1;
				while (++px < m->tile_size)
				{
					my_mlx_pixel_put(&m->minimap_map, x * m->tile_size + px,
						y * m->tile_size + py, get_tile_color(data, x, y));
				}
			}
		}
	}
}

static void	draw_minimap_pixel(t_data *data, t_minimap *m, int px, int py)
{
	int	dx;
	int	dy;
	int	map_x;
	int	map_y;
	int	color;

	dx = (int)(px * m->cos_a - py * m->sin_a);
	dy = (int)(px * m->sin_a + py * m->cos_a);
	map_x = (int)(data->player.x * m->tile_size) + dx;
	map_y = (int)(data->player.y * m->tile_size) + dy;
	if (map_x >= 0 && map_x < m->minimap_map.width
		&& map_y >= 0 && map_y < m->minimap_map.height)
	{
		color = get_pixel(&m->minimap_map, map_x, map_y);
		my_mlx_pixel_put(&data->image, px + m->center_x, py
			+ m->center_y, color);
	}
}

void	render_minimap(t_data *data)
{
	t_minimap	*m;
	int			py;
	int			px;

	m = &data->minimap;
	calc_minimap_transform(data, m);
	py = -m->radius_px - 1;
	while (++py <= m->radius_px)
	{
		px = -m->radius_px - 1;
		while (++px <= m->radius_px)
		{
			if (px * px + py * py > m->radius_px * m->radius_px)
				continue ;
			draw_minimap_pixel(data, m, px, py);
		}
	}
	draw_minimap_player(data);
	draw_minimap_border(data, 0xFFFFFF);
}

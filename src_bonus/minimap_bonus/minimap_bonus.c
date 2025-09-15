/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:26:44 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/16 01:26:44 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_minimap_border(t_data *data, int color)
{
	int	center;
	int	radius;
	int	angle;
	int	x;
	int	y;

	center = data->minimap.size / 2;
	radius = data->minimap.radius * data->minimap.tile_size;
	angle = 0;
	while (angle < 360)
	{
		x = center + (int)(cos(angle * PI / 180.0) * radius);
		y = center + (int)(sin(angle * PI / 180.0) * radius);
		my_mlx_pixel_put(&data->image, x, y, color);
		angle++;
	}
}

static int	get_tile_color(t_data *data, int x, int y)
{
	t_door	*door;
	char	cell;
	int		color;

	color = -1;
	if (x < 0 || x >= data->map.width || y < 0 || y >= data->map.height)
		return (color);
	cell = data->map.grid[y][x];
	if (cell == '1')
		color = data->minimap.wall_color;
	else if (cell == '0' || ft_strrchr("NSEW", cell))
		color = data->minimap.floor_color;
	else if (ft_strrchr("dDn", cell))
	{
		door = get_door_at_tile(&data->map, x, y);
		if (is_door_active(data, door))
			color = data->minimap.door_color;
		else
			color = data->minimap.wall_color;
	}
	return (color);
}

void	render_minimap(t_data *data, t_minimap *m)
{
	int	px;
	int	py;
	int	color;

	calc_minimap_transform(data, m);
	py = -1;
	while (++py < m->radius * 2 + 1)
	{
		m->map_y = m->start_tile_y + py;
		px = -1;
		while (++px < m->radius * 2 + 1)
		{
			m->map_x = m->start_tile_x + px;
			color = get_tile_color(data, m->map_x, m->map_y);
			if (color == -1)
				continue ;
			if (!minimap_tile_screen(m, px, py))
				continue ;
			draw_minimap_tile(data, m->screen_x, m->screen_y, color);
		}
	}
	draw_minimap_player(data);
	draw_minimap_border(data, 0xFFFFFF);
}

void	draw_minimap_tile(t_data *data, int screen_x, int screen_y, int color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	center;

	center = data->minimap.size / 2;
	y = 0;
	while (y < data->minimap.tile_size)
	{
		x = 0;
		while (x < data->minimap.tile_size)
		{
			dx = screen_x + x - center;
			dy = screen_y + y - center;
			if (dx * dx + dy * dy <= data->minimap.radius_px
				* data->minimap.radius_px)
				my_mlx_pixel_put(&data->image, screen_x + x, screen_y + y,
					color);
			x++;
		}
		y++;
	}
}

void	draw_minimap_player(t_data *data)
{
	int	radius;
	int	center_x;
	int	center_y;
	int	x;
	int	y;

	center_y = data->minimap.size / 2;
	center_x = data->minimap.size / 2;
	radius = data->minimap.tile_size / 2;
	if (radius < 2)
		radius = 2;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				my_mlx_pixel_put(&data->image, center_x + x, center_y + y,
					data->minimap.player_color);
			x++;
		}
		y++;
	}
}

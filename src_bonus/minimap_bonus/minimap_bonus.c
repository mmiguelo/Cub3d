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

static void	minimap_colorization(t_data *data, double x, double y)
{
	double	center_x;
	double	center_y;
	int		px;
	int		py;
	int		underlying_color;

	center_y = (data->minimap.size / 2);
	center_x = (data->minimap.size / 2);
	py = center_y + y;
	px = center_x + x;
	underlying_color = get_pixel(&data->image, px, py);
	if (underlying_color != data->minimap.wall_color)
		my_mlx_pixel_put(&data->image, px, py, data->minimap.player_color);
}

void	draw_minimap_player(t_data *data)
{
	double	radius;
	double	x;
	double	y;

	radius = data->minimap.tile_size / 3;
	if (radius < 2)
		radius = 2;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				minimap_colorization(data, x, y);
			x++;
		}
		y++;
	}
}

void	render_full_door_map(t_data *data)
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
			if (!ft_strrchr("dDn", data->map.grid[y][x]))
				continue ;
			py = -1;
			while (++py < m->tile_size)
			{
				px = -1;
				while (++px < m->tile_size)
					my_mlx_pixel_put(&m->minimap_map, x * m->tile_size + px,
						y * m->tile_size + py, get_tile_color(data, x, y));
			}
		}
	}
}

void	normalize_map(t_data *data, t_map *map)
{
	int		y;
	int		len;
	char	*new_row;

	y = 0;
	while (y < map->height)
	{
		len = ft_strlen(map->grid[y]);
		if (len < map->width)
		{
			new_row = malloc(map->width + 1);
			if (!new_row)
				ft_kill(data, ERR_MALLOC);
			ft_memcpy(new_row, map->grid[y], len);
			while (len < map->width)
				new_row[len++] = ' ';
			new_row[len] = '\0';
			free(map->grid[y]);
			map->grid[y] = new_row;
		}
		y++;
	}
}

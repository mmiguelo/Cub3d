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

void	render_minimap(t_data *data)
{
	int	y;
	int	x;
	int	px;
	int	py;

	y = -1;
	while (++y < data->map.height && data->map.grid[y])
	{
		x = -1;
		while (++x < data->map.width && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == '1')
				draw_minimap(data, x, y, data->minimap.wall_color);
			else if (data->map.grid[y][x] == '0')
				draw_minimap(data, x, y, data->minimap.floor_color);
			else if (data->map.grid[y][x] == 'N' || data->map.grid[y][x] == 'S'
				|| data->map.grid[y][x] == 'E' || data->map.grid[y][x] == 'W')
				draw_minimap(data, x, y, data->minimap.floor_color);
		}
	}
	px = (int)(data->player.x);
	py = (int)(data->player.y);
	draw_minimap_player(data, px, py);
}

void	draw_minimap(t_data *data, int map_x, int map_y, int color)
{
	int	y;
	int	x;
	int	start_x;
	int	start_y;

	start_x = map_x * data->minimap.tile_size;
	start_y = map_y * data->minimap.tile_size;
	y = -1;
	while (++y < data->minimap.tile_size)
	{
		x = -1;
		while (++x < data->minimap.tile_size)
			my_mlx_pixel_put(&data->image, start_x + x, start_y + y, color);
	}
}

void	draw_minimap_player(t_data *data, int tile_x, int tile_y)
{
	int	size;
	int	start_x;
	int	start_y;
	int	y;
	int	x;

	size = data->minimap.tile_size * 0.6;
	if (size < 2)
		size = 2;
	start_x = tile_x * data->minimap.tile_size
		+ (data->minimap.tile_size - size) / 2;
	start_y = tile_y * data->minimap.tile_size
		+ (data->minimap.tile_size - size) / 2;
	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
		{
			my_mlx_pixel_put(&data->image, start_x + x, start_y + y,
				data->minimap.player_color);
		}
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

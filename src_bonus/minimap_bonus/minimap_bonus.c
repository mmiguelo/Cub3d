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
	t_door	*door;
	int	y;
	int	x;

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
			else if (ft_strrchr("dDn", data->map.grid[y][x]))
			{
				door = find_door(&data->map, x, y);
				if (is_door_active(data, door))
					draw_minimap(data, x, y, data->minimap.door_color);
				else
					draw_minimap(data, x, y, data->minimap.wall_color);
			}
				
		}
	}
	draw_minimap_player(data);
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

void	draw_minimap_player(t_data *data)
{
	int	radius;
	int	center_x;
	int	center_y;
	int	y;
	int	x;

	radius = data->minimap.tile_size * 0.3 / 2;
	if (radius < 2)
		radius = 2;
	center_x = (int)(data->player.x * data->minimap.tile_size);
	center_y = (int)(data->player.y * data->minimap.tile_size);
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

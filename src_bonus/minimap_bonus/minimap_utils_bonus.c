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
	calculate_tile_size(data);
	data->minimap.floor_color = 0x000000;
	data->minimap.wall_color = 0xFFFFFF;
	data->minimap.player_color = 0x00FF00;
	data->minimap.door_color = 0xFF0000;
}

void	calculate_tile_size(t_data *data)
{
	int	max_width;
	int	max_height;
	int	tile_w;
	int	tile_h;

	max_width = WIN_WIDTH / 4;
	max_height = WIN_HEIGHT / 4;
	tile_w = max_width / data->map.width;
	tile_h = max_height / data->map.height;
	if (tile_w < tile_h)
		data->minimap.tile_size = tile_w;
	else
		data->minimap.tile_size = tile_h;
	if (data->minimap.tile_size < 2)
		data->minimap.tile_size = 2;
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

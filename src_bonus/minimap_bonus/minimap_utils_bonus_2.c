/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:16:51 by frbranda          #+#    #+#             */
/*   Updated: 2025/10/09 11:46:21 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	if (color == IGNORE)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_ignore(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	paint_in_ignore(t_img *img, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			my_mlx_pixel_ignore(img, x, y, color);
	}
}

void	init_img(t_img *img, void *mlx, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
		return ;
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_length, &img->endian);
	img->width = width;
	img->height = height;
}

int	get_tile_color(t_data *data, int x, int y)
{
	t_door	*door;
	char	cell;
	int		color;

	color = 0;
	if (x < 0 || y < 0 || x >= data->map.width || y >= data->map.height)
		return (IGNORE);
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
	if (color == IGNORE || color == 0)
		return (IGNORE);
	return (color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:00:41 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/13 13:00:41 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_fc(t_data *data)
{
	int		x;
	int		y;
	char	*pixel_addr;
	int		color;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				color = (data->ceiling.r << 16) | (data->ceiling.g << 8)
					| data->ceiling.b;
			else
			{
				color = (data->floor.r << 16) | (data->floor.g << 8)
					| data->floor.b;
			}
			pixel_addr = data->bg.addr + (y * data->bg.line_length)
				+ (x * (data->bg.bits_per_pixel / 8));
			*(unsigned int *)pixel_addr = color;
		}
	}
}

void	calculate_texture(t_data *data, t_ray *ray)
{
	if (ray->draw.side == 0)
		ray->draw.wallx = data->player.y + ray->draw.perpwalldist * ray->dir.y;
	else
		ray->draw.wallx = data->player.x + ray->draw.perpwalldist * ray->dir.x;
	ray->draw.wallx -= floor(ray->draw.wallx);
	ray->draw.tex_x = (int)(ray->draw.wallx * TILE_SIZE);
	if (ray->draw.side == 0 && ray->dir.x > 0)
		ray->draw.tex_x = TILE_SIZE - ray->draw.tex_x - 1;
	if (ray->draw.side == 1 && ray->dir.y < 0)
		ray->draw.tex_x = TILE_SIZE - ray->draw.tex_x - 1;
	ray->draw.step = 1.0 * TILE_SIZE / ray->draw.line_height;
	ray->draw.tex_pos = (ray->draw.start - PITCH - WIN_HEIGHT / 2
			+ ray->draw.line_height / 2) * ray->draw.step;
}

void	draw_line(t_data *data, t_ray *ray, int x)
{
	ray->draw.tex_y = ray->draw.tex_pos;
	ray->draw.tex_pos += ray->draw.step;
	if (ray->draw.side == 0 && ray->dir.x > 0)
		ray->draw.color = color(&ray->draw, &data->textures.west);
	else if (ray->draw.side == 0 && ray->dir.x < 0)
		ray->draw.color = color(&ray->draw, &data->textures.east);
	else if (ray->draw.side == 1 && ray->dir.y > 0)
		ray->draw.color = color(&ray->draw, &data->textures.south);
	else
		ray->draw.color = color(&ray->draw, &data->textures.north);
	put_pixel(&data->bg, x, ray->draw.start, ray->draw.color);
	ray->draw.start++;
}

int	color(t_draw *draw, t_img *texture)
{
	return (*(int *)(texture->addr + (draw->tex_y * texture->line_length
			+ draw->tex_x * (texture->bits_per_pixel / 8))));
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (y < 0 || y > WIN_HEIGHT - 1 || x < 0
		|| x > WIN_WIDTH - 1)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

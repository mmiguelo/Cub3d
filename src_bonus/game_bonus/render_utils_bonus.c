/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:01:40 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/14 23:01:40 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	render_fc_pixel(t_data *data, t_fccast *fc, t_img *texture)
{
	int		tex_color;
	double	brightness;

	data->ray.draw.tex_x = (int)(fc->tex.x * texture->width) % texture->width;
	data->ray.draw.tex_y = (int)(fc->tex.y * texture->height) % texture->height;
	if (data->ray.draw.tex_x < 0)
		data->ray.draw.tex_x += texture->width;
	if (data->ray.draw.tex_y < 0)
		data->ray.draw.tex_y += texture->height;
	brightness = 1.0 / (1.0 + fc->row_distance * DARKNESS);
	if (brightness < 0.2)
		brightness = 0.2;
	tex_color = color(&data->ray.draw, texture);
	tex_color = apply_global_brightness(tex_color, data->global_light
			* brightness);
	draw_pixel(&data->image, fc->temp.x, fc->temp.y, tex_color);
}

void	render_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->draw.side == 0 && ray->dir.x > 0)
		ray->draw.color = color(&ray->draw, &data->textures.west);
	else if (ray->draw.side == 0 && ray->dir.x < 0)
		ray->draw.color = color(&ray->draw, &data->textures.east);
	else if (ray->draw.side == 1 && ray->dir.y < 0)
		ray->draw.color = color(&ray->draw, &data->textures.south);
	else
		ray->draw.color = color(&ray->draw, &data->textures.north);
}

int	color(t_draw *draw, t_img *texture)
{
	int	pixel;

	pixel = *(int *)(texture->addr + (draw->tex_y * texture->line_length
				+ draw->tex_x * (texture->bpp / 8)));
	if (pixel == IGNORE)
		return (-1);
	return (pixel);
}

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (y < 0 || y > WIN_HEIGHT - 1 || x < 0
		|| x > WIN_WIDTH - 1)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	update_time_of_day(t_data *data)
{
	data->time_of_day += DAY_NIGHT_CYCLE;
	if (data->time_of_day >= 1.0)
		data->time_of_day -= 1.0;
}

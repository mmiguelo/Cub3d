/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:23:51 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/09/17 12:27:38 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	handle_wall_or_door(t_data *data, t_ray *ray)
{
	t_door	*door;
	char	cell;
	int		tex_y_int;

	cell = data->map.grid[data->ray.pos.y][data->ray.pos.x];
	tex_y_int = (int)ray->draw.tex_pos;
	if (tex_y_int < -TILE_SIZE * 2)
		tex_y_int = -TILE_SIZE * 2;
	ray->draw.tex_y = tex_y_int;
	ray->draw.tex_pos += ray->draw.step;
	if (cell == 'D' || cell == 'd' || cell == 'n')
	{
		door = get_door_at_tile(&data->map, ray->pos.x, ray->pos.y);
		if (door && door->active)
			sample_door_texture(data, ray, door);
		else
			render_wall_texture(data, ray);
	}
	else
		render_wall_texture(data, ray);
}

void	apply_lighting(t_data *data, t_ray *ray, int x)
{
	double	total_light;

	ray->draw.brightness = 1 / (1 + ray->draw.perpwalldist * DARKNESS);
	if (ray->draw.brightness < 0.2)
		ray->draw.brightness = 0.2;
	total_light = ray->draw.brightness * data->global_light;
	ray->draw.color = apply_brightness(ray->draw.color, total_light);
	if (ray->draw.color != -1)
		draw_pixel(&data->image, x, ray->draw.start, ray->draw.color);
}

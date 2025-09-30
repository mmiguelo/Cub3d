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

#include "cub3D_bonus.h"

void	put_fc(t_data *data)
{
	int		x;
	int		y;
	char	*pixel_addr;
	int		sky_color;
	int		floor_color;

	init_fc_directions(data, &data->ray.fc);
	sky_color = lerp_day_cycle(data, data->time_of_day);
	sky_color = apply_global_brightness(sky_color, data->global_light);
	floor_color = (data->floor.r << 16) | (data->floor.g << 8) | data->floor.b;
	floor_color = apply_global_brightness(floor_color, data->global_light);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			pixel_addr = data->image.addr + (y * data->image.line_length)
				+ (x * (data->image.bpp / 8));
			if (y < data->ray.fc.horizon)
				*(unsigned int *)pixel_addr = sky_color;
			else
				*(unsigned int *)pixel_addr = floor_color;
		}
	}
}

void	calculate_texture(t_data *data, t_ray *ray)
{
	int horizon;

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
	if (ray->draw.tex_x < 0)
		ray->draw.tex_x = 0;
	if (ray->draw.tex_x >= TILE_SIZE)
		ray->draw.tex_x = TILE_SIZE - 1;
	ray->draw.step = 1.0 * TILE_SIZE / ray->draw.line_height;
	if (ray->draw.step < 0.01)
    ray->draw.step = 0.01;
	horizon = (int)(WIN_HEIGHT / 2 + (data->player.height - 0.5) * WIN_HEIGHT);
	ray->draw.tex_pos = (ray->draw.start - horizon + ray->draw.line_height / 2.0) * ray->draw.step;
	if (ray->draw.tex_pos < -TILE_SIZE * 2.0)
		ray->draw.tex_pos = -TILE_SIZE * 2.0;
}

void	draw_line(t_data *data, t_ray *ray, int x)
{
	if (data->ray.pos.x < 0 || data->ray.pos.x >= data->map.width
		|| data->ray.pos.y < 0 || data->ray.pos.y >= data->map.height)
	{
		ray->draw.start++;
		return ;
	}
	handle_wall_or_door(data, ray);
	if (ray->draw.color == -1)
	{
		data->ray.draw.hit = false;
		while (!data->ray.draw.hit)
			check_hit(data, &data->ray);
		calculate_perpwalldist(data, &ray->draw);
		calculate_texture(data, ray);
		return ;
	}
	apply_lighting(data, ray, x);
	ray->draw.start++;
}

void	render_column(t_data *data, int x)
{
	data->ray.draw.hit = false;
	calculate_variables(&data->player, &data->ray, x);
	while (!data->ray.draw.hit)
		check_hit(data, &data->ray);
	calculate_perpwalldist(data, &data->ray.draw);
	calculate_texture(data, &data->ray);
	if (data->ray.draw.start > data->ray.draw.end)
		data->ray.draw.start = data->ray.draw.end;
	while (data->ray.draw.start < data->ray.draw.end)
		draw_line(data, &data->ray, x);
}

void	check_hit(t_data *data, t_ray *ray)
{
	if (ray->step.side_dist_x < ray->step.side_dist_y)
	{
		ray->step.side_dist_x += ray->step.delta_dist_x;
		ray->pos.x += ray->step.x;
		ray->draw.side = 0;
	}
	else
	{
		ray->step.side_dist_y += ray->step.delta_dist_y;
		ray->pos.y += ray->step.y;
		ray->draw.side = 1;
	}
	if (ray->pos.x >= 0 && ray->pos.x < data->map.width
		&& ray->pos.y >= 0 && ray->pos.y < data->map.height)
	{
		if (data->map.grid[ray->pos.y][ray->pos.x] == '1')
			ray->draw.hit = true;
		else if (ft_strchr("Ddn", data->map.grid[ray->pos.y][ray->pos.x]))
			ray->draw.hit = true;
		else
			ray->draw.hit = false;
	}
	else
		ray->draw.hit = true;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:00:45 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/13 13:00:45 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	calculate_raycasting(t_data *data)
{
	t_ray	ray;
	int		x;

	clear_image(&data->image, 0x000000);
	put_fc(data);
	x = 0;
	while (x < WIN_WIDTH)
	{
		ray.draw.hit = false;
		calculate_variables(&data->player, &ray, x);
		while (ray.draw.hit == false)
			check_hit(data, &ray);
		calculate_perpwalldist(&ray, &ray.draw);
		calculate_texture(data, &ray);
		while (ray.draw.start < ray.draw.end)
			draw_line(data, &ray, x);
		x++;
	}
	copy_bg_to_image(&data->bg, &data->image);
	update_global_light(data);
	if (MINIMAP_ENABLED)
		render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
}

void	calculate_variables(t_player *player, t_ray *ray, int x)
{
	ray->pos.x = (int)player->x;
	ray->pos.y = (int)player->y;
	ray->cam.screen_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir.x = player->dir.x + player->plane.x * ray->cam.screen_x;
	ray->dir.y = player->dir.y + player->plane.y * ray->cam.screen_x;
	if (ray->dir.x == 0)
		ray->step.delta_dist_x = 1e30;
	else
		ray->step.delta_dist_x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->step.delta_dist_y = 1e30;
	else
		ray->step.delta_dist_y = fabs(1 / ray->dir.y);
	calculate_variables2(ray, player->x, player->y);
}

void	calculate_variables2(t_ray *ray, double player_x, double player_y)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->step.side_dist_x = (player_x - ray->pos.x)
			* ray->step.delta_dist_x;
	}
	else
	{
		ray->step.x = 1;
		ray->step.side_dist_x = (ray->pos.x + 1.0 - player_x)
			* ray->step.delta_dist_x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->step.side_dist_y = (player_y - ray->pos.y)
			* ray->step.delta_dist_y;
	}
	else
	{
		ray->step.y = 1;
		ray->step.side_dist_y = (ray->pos.y + 1.0 - player_y)
			* ray->step.delta_dist_y;
	}
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
		else if (data->map.grid[ray->pos.y][ray->pos.x] == '0')
			ray->draw.hit = false;
	}
	else
		ray->draw.hit = true;
}

void	calculate_perpwalldist(t_ray *ray, t_draw *draw)
{
	if (draw->side == 0)
		draw->perpwalldist = ray->step.side_dist_x - ray->step.delta_dist_x;
	else
		draw->perpwalldist = ray->step.side_dist_y - ray->step.delta_dist_y;
	draw->line_height = (int)(WIN_HEIGHT / draw->perpwalldist);
	draw->start = -draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->end >= WIN_HEIGHT)
		draw->end = WIN_HEIGHT - 1;
}

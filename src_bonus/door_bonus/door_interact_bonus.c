/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interact_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:26:17 by frbranda          #+#    #+#             */
/*   Updated: 2025/10/09 10:26:18 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	init_interact_door(t_player *player, t_ray *ray, t_doorcast *dc)
{
	calculate_variables(player, ray, WIN_WIDTH / 2);
	dc->map.x = ray->pos.x;
	dc->map.y = ray->pos.y;
	dc->start.x = dc->map.x;
	dc->start.y = dc->map.y;
	dc->dist = 0.0;
}

static void	door_dda_step(t_ray *ray, t_doorcast *dc)
{
	if (ray->step.side_dist_x < ray->step.side_dist_y)
	{
		ray->step.side_dist_x += ray->step.delta_dist_x;
		dc->map.x += ray->step.x;
		dc->dist = (ray->step.side_dist_x - ray->step.delta_dist_x);
	}
	else
	{
		ray->step.side_dist_y += ray->step.delta_dist_y;
		dc->map.y += ray->step.y;
		dc->dist = (ray->step.side_dist_y - ray->step.delta_dist_y);
	}
}

void	toggle_door_state(t_data *data)
{
	t_ray		ray;
	t_door		*door;
	t_doorcast	dc;

	init_interact_door(&data->player, &ray, &dc);
	while (dc.dist < INTERACT_RANGE)
	{
		door_dda_step(&ray, &dc);
		if (dc.map.x < 0 || dc.map.x >= data->map.width
			|| dc.map.y < 0 || dc.map.y >= data->map.height)
			break ;
		if (dc.map.x == dc.start.x && dc.map.y == dc.start.y)
			continue ;
		door = get_door_at_tile(&data->map, dc.map.x, dc.map.y);
		if (door && is_door_active(data, door))
		{
			if (door->state == DOOR_CLOSED)
				door->state = DOOR_OPENING;
			else if (door->state == DOOR_OPEN)
				door->state = DOOR_CLOSING;
			return ;
		}
		if (data->map.grid[dc.map.y][dc.map.x] == '1')
			break ;
	}
}

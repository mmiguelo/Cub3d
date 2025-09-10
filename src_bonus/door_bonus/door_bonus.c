/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 02:27:34 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/09/03 02:27:34 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_door	*find_nearby_door(t_data *data, double px, double py, double max_dist)
{
	int		i;
	double	dx;
	double	dy;
	double	dist;
	t_door	*door;

	i = 0;
	while (i < data->map.door_count)
	{
		door = &data->map.doors[i];
		dx = px - (door->x + 0.5);
		dy = py - (door->y + 0.5);
		dist = sqrt(dx * dx + dy * dy);
		if (dist <= max_dist)
			return (door);
		i++;
	}
	return (NULL);
}

void	render_door(t_data *data, t_ray *ray)
{
	t_door	*door;
	int		active;

	door = find_door(&data->map, ray->pos.x, ray->pos.y);
	if (!door)
		return ;
	active = is_door_active(data, door);
	if (!active)
	{
		door->tile = '1';
		ray->draw.hit = true;
		return ;
	}
	door->tile = 'D';
	ray->draw.hit = true;
}

void	update_doors(t_data *data)
{
	t_door	*door;
	char	cell;
	int		i;

	i = -1;
	while (++i < data->map.door_count)
	{
		door = &data->map.doors[i];
		cell = data->map.grid[door->y][door->x];
		if (cell == 'D')
			door->active = 1;
		else if (cell == 'd')
			door->active = (data->bsun || data->bsunrise || player_inside_door(data, door));
		else if (cell == 'n')
			door->active = (data->bsunset || data->bmoon || player_inside_door(data, door));
		else 
			door->active = player_inside_door(data, door);
		if (door->active)
		{
			if (door->state == DOOR_OPENING && door->frame < 14)
				door->frame++;
			else if (door->state == DOOR_OPENING && door->frame == 14)
				door->state = DOOR_OPEN;
			else if (door->state == DOOR_CLOSING && door->frame > 0)
				door->frame--;
			else if (door->state == DOOR_CLOSING && door->frame == 0)
				door->state = DOOR_CLOSED;
		}
	}
}

void	engage_door(t_data *data, t_door *door, t_door_state new_state)
{
	door->timer += data->frames.delta_time;
	if (door->timer >= 1.0 / DOOR_FPS)
	{
		door->timer = 0;
		if (new_state == DOOR_OPENING)
		{
			door->frame++;
			if (door->frame >= 14)
			{
				door->frame = 14;
				door->state = DOOR_OPEN;
			}
		}
		else if (new_state == DOOR_CLOSING)
		{
			door->frame--;
			if (door->frame <= 0)
			{
				door->frame = 0;
				door->state = DOOR_CLOSED;
			}
		}
	}
}

void	find_which_door_texture(t_data *data, t_ray *ray, t_door *door)
{
	t_img	*texture;
	int		tex_x;
	int		tex_y;
	int		local_y;
	int		col;
	int		row;

	texture = &data->door_spritesheet;
	if (door->frame < 0)
		door->frame = 0;
	if (door->frame > 14)
		door->frame = 14;
	col = door->frame % 5;
	row = door->frame / 5;
	tex_x = (int)(ray->draw.wallx * TILE_SIZE);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TILE_SIZE)
		tex_x = TILE_SIZE - 1;
	local_y = (int)ray->draw.tex_pos;
	tex_y = local_y % TILE_SIZE;
	if (tex_y < 0)
		tex_y += TILE_SIZE;
	ray->draw.tex_x = tex_x + col * TILE_SIZE;
	ray->draw.tex_y = tex_y + row * TILE_SIZE;
	ray->draw.color = color(&ray->draw, texture);
}

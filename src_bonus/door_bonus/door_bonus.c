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

/* t_door	*find_nearby_door(t_data *data, double px, double py, double max_dist)
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
} */

void	draw_door(t_data *data, t_door *door, int x)
{
	int	active;
	t_draw	*draw;

	active = is_door_active(data, door);
	if (!active)
		door->tile = '1';
	else
		door->tile = 'D';
	draw = &door->draw;
	draw->line_height = (int)(WIN_HEIGHT / door->door_dist);
	draw->start = -draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->end >= WIN_HEIGHT)
		draw->end = WIN_HEIGHT - 1;
	draw->tex_x = (int)(door->wall_hit * door->current.width);
	if ((door->door_side == 0 && data->ray.dir.x > 0)
		|| (door->door_side == 1 && data->ray.dir.y < 0))
		draw->tex_x = door->current.width - draw->tex_x - 1;
	draw->tex_x %= door->current.width;
	draw->step = (double)door->current.height / draw->height;
	draw->tex_pos = (draw->start - WIN_HEIGHT / 2 + draw->line_height / 2) \
		* draw->step;	

}

void	render_door(t_data *data, t_ray *ray, int x)
{
	t_door	*door;
	int		index;

	while (ray->door_increment > -1)
	{
		index = ft_find_door_index(&data->map,
			ray->doors_found[ray->door_increment].x,
			ray->doors_found[ray->door_increment].y);
		door = &data->map.doors[index];
		if (door->door_side == 0)
			door->wall_hit = data->player.y + door->door_dist * ray->dir.y;
		else
			door->wall_hit = data->player.x + door->door_dist * ray->dir.x;
		door->wall_hit -= floor(door->wall_hit);
		draw_door(data, &door, x);
		ray->door_increment--;
	}
	ray->hit_door = false;
	ray->door_increment = -1;
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
			door->active = (data->bsun || data->bsunrise);
		else if (cell == 'n')
			door->active = (data->bsunset || data->bmoon);
		else
			door->active = 0;
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
				door->open = true;
			}
		}
		else if (new_state == DOOR_CLOSING)
		{
			door->frame--;
			if (door->frame <= 0)
			{
				door->frame = 0;
				door->state = DOOR_CLOSED;
				door->open = false;
			}
		}
	}
}

/* void	find_which_door_texture(t_data *data, t_ray *ray, t_door *door)
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
} */

int	ft_find_door_index(t_map *map, int x, int y)
{
	int	i;

	i = 0;
	while (i < map->door_count)
	{
		if (x == map->doors[i].x
			&& y == (map->doors)[i].y)
			return (i);
		i++;
	}
	return (-1);
}

void	get_door_info(t_ray *ray, t_map *map)
{
	int	index;

	ray->door_increment++;
	if (ray->door_increment == -1)
		return ;
	ray->doors_found[ray->door_increment].x = ray->step.x;
	ray->doors_found[ray->door_increment].y = ray->step.y;
	index = ft_find_door_index(map, ray->step.x, ray->step.y);
	ray->hit_door = true;
	map->doors[index].x = ray->step.x;
	map->doors[index].y = ray->step.y;
	map->doors[index].door_side = ray->draw.side;
	if (ray->draw.side == 0)
		map->doors[index].door_dist = ray->step.side_dist_x - ray->step.side_dist_x;
	else
		map->doors[index].door_dist = ray->step.side_dist_y - ray->step.side_dist_y;
}

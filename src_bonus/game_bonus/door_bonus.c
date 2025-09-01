#include "cub3D_bonus.h"

t_door	*find_door(t_map *map, int x, int y)
{
	int	i;

	i = 0;
	while (i < map->door_count)
	{
		if (map->doors[i].x == x && map->doors[i].y == y)
			return (&map->doors[i]);
		i++;
	}
	return (NULL);
}

t_door *find_nearby_door(t_data *data, double px, double py, double max_dist)
{
	int		i;
	double	dx;
	double	dy;
	double	dist;

	i = 0;
	while (i < data->map.door_count)
	{
		t_door *door = &data->map.doors[i];
		dx = px - (door->x + 0.5);
		dy = py - (door->y + 0.5);
		dist = sqrt(dx * dx + dy * dy);
		if (dist <= max_dist)
			return door;
		i++;
	}
	return NULL;
}


int	is_door_active(t_data *data, t_door *door)
{
	if (!door)
		return (0);
	if (door->mode == DOOR_DAY && data->bsunrise)
		return (1);
	if (door->mode == DOOR_NIGHT && data->bmoon)
		return (1);
	if (door->mode == DOOR_ALWAYS)
		return (1);
	return (0);
}

void render_door(t_data *data, t_ray *ray)
{
	t_door	*door;
	int	active;

	door = find_door(&data->map, ray->pos.x, ray->pos.y);
	active = is_door_active(data, door);
	if (!active)
	{
		ray->draw.hit = true;
		data->map.doors->tile = '1';
	}
	else if (active && door && !door->open)
	{
		ray->draw.hit = true;
		data->map.doors->tile = 'D';
	}
	else if (active && door && door->open)
	{
		ray->draw.hit = false;
		data->map.doors->tile = 'D';
	}
}

void	update_doors(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->map.door_count)
	{
		t_door *door = &data->map.doors[i];

		if (door->state == DOOR_OPENING)
			engage_door(data, door, DOOR_OPENING);
		else if (door->state == DOOR_CLOSING)
			engage_door(data, door, DOOR_CLOSING);
		if (door->state == DOOR_OPEN && !is_door_active(data, door))
			door->state = DOOR_CLOSING;
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

void	find_which_door_texture(t_data *data, t_ray *ray)
{
	t_door	*door;
	t_img	*texture;
	int		tex_x;
	int		tex_y;
	int		local_y;

	door = find_door(&data->map, ray->pos.x, ray->pos.y);
	texture = &data->door_spritesheet;
	door->col = door->frame % 5;
	door->row = door->frame / 5;
	tex_x = (int)(ray->draw.wallx * TILE_SIZE);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TILE_SIZE)
		tex_x = TILE_SIZE - 1;
	local_y = (int)ray->draw.tex_pos;
	tex_y = local_y % TILE_SIZE;
	if (tex_y < 0)
		tex_y += TILE_SIZE;
	ray->draw.tex_x = tex_x + door->col * TILE_SIZE;
	ray->draw.tex_y = tex_y + door->row * TILE_SIZE;
	ray->draw.color = color(&ray->draw, texture);
}

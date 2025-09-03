#include "cub3D_bonus.h"

void	change_door_state(t_data *data)
{
	t_door	*door;
	int		map_x;
	int		map_y;

	map_x = ((int)data->player.x + (int)data->ray.dir.x);
	map_y = ((int)data->player.y + (int)data->ray.dir.y);
	door = find_door(&data->map, map_x, map_y);
	if (door && is_door_active(data, door))
	{
		if (door->state == DOOR_CLOSED)
			door->state = DOOR_OPENING;
		else if (door->state == DOOR_OPEN)
			door->state = DOOR_CLOSING;
	}
}

int	is_door_active(t_data *data, t_door *door)
{
	if (!door)
		return (0);
	if (door->mode == DOOR_DAY && (data->bsun || data->bsunrise))
		return (1);
	if (door->mode == DOOR_NIGHT && (data->bsunset || data->bmoon))
		return (1);
	if (door->mode == DOOR_ALWAYS)
		return (1);
	return (0);
}

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

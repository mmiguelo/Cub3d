/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_util_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:15:08 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/09/12 12:15:08 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

t_door	*get_door_at_tile(t_map *map, int x, int y)
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

int	player_inside_door(t_data *data, t_door *door)
{
	if (data->player.x + PLAYER_RAD > door->x
		&& data->player.x - PLAYER_RAD < door->x + 1
		&& data->player.y + PLAYER_RAD > door->y
		&& data->player.y - PLAYER_RAD < door->y + 1)
		return (1);
	return (0);
}

void	update_door_frame(t_door *door)
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

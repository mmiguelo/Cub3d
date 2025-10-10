/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:15:25 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/10/10 09:38:24 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	is_blocking_tile(t_data *data, int x, int y)
{
	t_door	*door;
	char	tile;

	tile = data->map.grid[y][x];
	if (tile == '1')
		return (1);
	if (tile == 'D' || tile == 'd' || tile == 'n')
	{
		door = get_door_at_tile(&data->map, x, y);
		if (player_inside_door(data, door))
			return (0);
		if (!door || !door->active)
			return (1);
		if (door->state != DOOR_OPEN)
			return (1);
		return (0);
	}
	return (0);
}

int	can_move(t_data *data, double x, double y)
{
	return (
		!is_blocking_tile(data, (int)(x + PLAYER_RAD), (int)(y + PLAYER_RAD)) &&
		!is_blocking_tile(data, (int)(x - PLAYER_RAD), (int)(y + PLAYER_RAD)) &&
		!is_blocking_tile(data, (int)(x + PLAYER_RAD), (int)(y - PLAYER_RAD)) &&
		!is_blocking_tile(data, (int)(x - PLAYER_RAD), (int)(y - PLAYER_RAD))
	);
}

void	check_collision(t_data *data, t_player *player)
{
	if (can_move(data, player->new_x, player->y))
		player->x = player->new_x;
	if (can_move(data, player->x, player->new_y))
		player->y = player->new_y;
}

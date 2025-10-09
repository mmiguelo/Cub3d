/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:25:32 by frbranda          #+#    #+#             */
/*   Updated: 2025/10/09 10:25:36 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_blocking_tile(t_data *data, int x, int y)
{
	char	tile;

	tile = data->map.grid[y][x];
	if (tile == '1')
		return (1);
	return (0);
}

static int	can_move(t_data *data, double x, double y)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_parse_doors_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:19:05 by frbranda          #+#    #+#             */
/*   Updated: 2025/10/09 14:20:54 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	check_doors(t_data *data, int x, int y)
{
	int	wall_count;

	wall_count = 0;
	if (data->map.grid[y][x + 1] == '1')
		wall_count++;
	if (data->map.grid[y][x - 1] == '1')
		wall_count++;
	if (data->map.grid[y + 1][x] == '1')
		wall_count++;
	if (data->map.grid[y - 1][x] == '1')
		wall_count++;
	if (wall_count < 2)
		ft_kill(data, "Door must be placed between at least two walls");
	else if (wall_count == 2)
	{
		if ((data->map.grid[y][x + 1] == '1' && data->map.grid[y][x - 1] != '1')
			|| (data->map.grid[y][x - 1] == '1'
				&& data->map.grid[y][x + 1] != '1')
			|| (data->map.grid[y + 1][x] == '1' &&
				data->map.grid[y - 1][x] != '1')
			|| (data->map.grid[y - 1][x] == '1'
				&& data->map.grid[y + 1][x] != '1'))
			ft_kill(data, "Door must be placed between two walls adjacently");
	}
}

void	parse_door(t_data *data, int x, int y)
{
	t_door	*door;

	if (data->map.door_count >= MAX_DOORS)
		ft_kill(data, "Too many doors in map");
	check_doors(data, x, y);
	door = &data->map.doors[data->map.door_count++];
	door->x = x;
	door->y = y;
	door->state = DOOR_CLOSED;
	door->tile = '1';
	if (data->map.grid[y][x] == 'D')
		door->mode = DOOR_ALWAYS;
	else if (data->map.grid[y][x] == 'd')
		door->mode = DOOR_DAY;
	else if (data->map.grid[y][x] == 'n')
		door->mode = DOOR_NIGHT;
}

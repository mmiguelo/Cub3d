/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:00:53 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/13 13:00:53 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_movements(t_data *data)
{
	if (data->player.move_forward)
	{
		data->player.new_x = data->player.x + data->player.dir.x * SPEED;
		data->player.new_y = data->player.y + data->player.dir.y * SPEED;
		check_collision(data, &data->player);
	}
	if (data->player.move_backward)
	{
		data->player.new_x = data->player.x - data->player.dir.x * SPEED;
		data->player.new_y = data->player.y - data->player.dir.y * SPEED;
		check_collision(data, &data->player);
	}
	move_strafe(data);
	turn_player(&data->player);
}

void	move_strafe(t_data *data)
{
	if (data->player.move_left)
	{
		data->player.new_x = data->player.x + data->player.dir.y * SPEED;
		data->player.new_y = data->player.y - data->player.dir.x * SPEED;
		check_collision(data, &data->player);
	}
	if (data->player.move_right)
	{
		data->player.new_x = data->player.x - data->player.dir.y * SPEED;
		data->player.new_y = data->player.y + data->player.dir.x * SPEED;
		check_collision(data, &data->player);
	}
}

void	turn_player(t_player *player)
{
	if (player->turn_left)
		calculate_rotation(player, -ROT_SPEED);
	if (player->turn_right)
		calculate_rotation(player, ROT_SPEED);
}

void	calculate_rotation(t_player *player, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(rotation_speed) - player->dir.y
		* sin(rotation_speed);
	player->dir.y = old_dir_x * sin(rotation_speed) + player->dir.y
		* cos(rotation_speed);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(rotation_speed) - player->plane.y
		* sin(rotation_speed);
	player->plane.y = old_plane_x * sin(rotation_speed) + player->plane.y
		* cos(rotation_speed);
}

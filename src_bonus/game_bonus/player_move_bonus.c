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

#include "cub3D_bonus.h"

void	calculate_movements(t_data *data)
{
	double		speed_mult;
	t_player	*player;

	player = &data->player;
	speed_mult = 1.0;
	if (player->sprint)
		speed_mult = 4.0;
	if (player->move_forward)
	{
		player->new_x = player->x + player->dir.x * SPEED * speed_mult;
		player->new_y = player->y + player->dir.y * SPEED * speed_mult;
		check_collision(data, player);
	}
	if (player->move_backward)
	{
		player->new_x = player->x - player->dir.x * SPEED * speed_mult;
		player->new_y = player->y - player->dir.y * SPEED * speed_mult;
		check_collision(data, player);
	}
	move_strafe(data);
	turn_player(player);
}

void	move_strafe(t_data *data)
{
	double		speed_mult;
	t_player	*player;

	player = &data->player;
	speed_mult = 1.0;
	if (player->sprint)
		speed_mult = 4.0;
	if (player->move_left)
	{
		player->new_x = player->x + player->dir.y * SPEED * speed_mult;
		player->new_y = player->y - player->dir.x * SPEED * speed_mult;
		check_collision(data, player);
	}
	if (player->move_right)
	{
		player->new_x = player->x - player->dir.y * SPEED * speed_mult;
		player->new_y = player->y + player->dir.x * SPEED * speed_mult;
		check_collision(data, player);
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

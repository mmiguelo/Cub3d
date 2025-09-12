/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_handler_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:00:56 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/09/12 11:42:21 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	key_hook_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data, GAME_ENDED);
	if (keycode == XK_w)
		data->player.move_forward = 1;
	if (keycode == XK_s)
		data->player.move_backward = 1;
	if (keycode == XK_d)
		data->player.move_right = 1;
	if (keycode == XK_a)
		data->player.move_left = 1;
	if (keycode == XK_Left)
		data->player.turn_left = 1;
	if (keycode == XK_Right)
		data->player.turn_right = 1;
	if (keycode == XK_space)
		data->player.sprint = 1;
	if (keycode == XK_e)
		change_door_state(data);
	if (keycode == XK_f)
		toggle_flashlight(data);
	return (0);
}

int	key_hook_release(int keycode, t_data *data)
{
	if (keycode == XK_w && data->player.move_forward)
		data->player.move_forward = 0;
	if (keycode == XK_s && data->player.move_backward)
		data->player.move_backward = 0;
	if (keycode == XK_a && data->player.move_left)
		data->player.move_left = 0;
	if (keycode == XK_d && data->player.move_right)
		data->player.move_right = 0;
	if (keycode == XK_Left && data->player.turn_left)
		data->player.turn_left = 0;
	if (keycode == XK_Right && data->player.turn_right)
		data->player.turn_right = 0;
	if (keycode == XK_space && data->player.sprint)
		data->player.sprint = 0;
	return (0);
}

int	x_press(t_data *data)
{
	mlx_loop_end(data->mlx);
	close_window(data, GAME_ENDED);
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)y;
	if (x < WIN_WIDTH / 2)
		calculate_rotation(&data->player, -ROT_SPEED);
	else if (x > WIN_WIDTH / 2)
		calculate_rotation(&data->player, ROT_SPEED);
	mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, y);
	return (0);
}

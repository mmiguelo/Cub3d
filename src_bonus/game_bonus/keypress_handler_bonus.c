/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_handler_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:00:56 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/10/09 12:29:00 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	handle_actions(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data, GAME_ENDED);
	if (keycode == XK_e)
		toggle_door_state(data);
	if (keycode == XK_f)
		toggle_flashlight(data);
	if (keycode == XK_r)
		data->player.height = P_HEIGHT;
	if (keycode == XK_t)
		data->indoor = !data->indoor;
}

int	key_hook_press(int keycode, t_data *data)
{
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
	if (keycode == XK_Up)
		data->player.look_up = 1;
	if (keycode == XK_Down)
		data->player.look_down = 1;
	if (keycode == XK_Shift_L)
		data->player.sprint = 1;
	handle_actions(keycode, data);
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
	if (keycode == XK_Up && data->player.look_up)
		data->player.look_up = 0;
	if (keycode == XK_Down && data->player.look_down)
		data->player.look_down = 0;
	if (keycode == XK_Shift_L && data->player.sprint)
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
	if (y < WIN_HEIGHT / 2)
	{
		data->player.height += (ROT_SPEED * 0.4);
		if (data->player.height < 0.0)
			data->player.height = 0.0;
	}
	else if (y > WIN_HEIGHT / 2)
	{
		data->player.height -= (ROT_SPEED * 0.4);
		if (data->player.height > 1.0)
			data->player.height = 1.0;
	}
	if (x < WIN_WIDTH / 2)
		calculate_rotation(&data->player, -(ROT_SPEED * 0.4));
	else if (x > WIN_WIDTH / 2)
		calculate_rotation(&data->player, (ROT_SPEED * 0.4));
	mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}

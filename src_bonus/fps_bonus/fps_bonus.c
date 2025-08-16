/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:20:32 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/16 01:20:32 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_fps(t_data *data)
{
	int	i;

	i = 0;
	data->frames.time = 0.0;
	data->frames.old_time = get_current_time_in_seconds();
	data->frames.delta_time = 0.0;
	data->frames.fps = 0.0;
	data->frames.fps_index = 0;
	while (i < FPS_HISTORY_SIZE)
	{
		data->frames.fps_history[i] = 0.0;
		i++;
	}
}

double	get_current_time_in_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	update_fps(t_data *data)
{
	double	current_fps;
	double	sum;
	int		i;

	i = -1;
	sum = 0.0;
	data->frames.time = get_current_time_in_seconds();
	data->frames.delta_time = data->frames.time - data->frames.old_time;
	if (data->frames.delta_time <= 0.0)
		data->frames.delta_time = 0.0001;
	data->frames.old_time = data->frames.time;
	current_fps = 1.0 / data->frames.delta_time;
	data->frames.fps_history[data->frames.fps_index] = current_fps;
	data->frames.fps_index = (data->frames.fps_index + 1) % FPS_HISTORY_SIZE;
	while (++i < FPS_HISTORY_SIZE)
		sum += data->frames.fps_history[i];
	data->frames.fps = sum / FPS_HISTORY_SIZE;
}

void	render_fps(t_data *data)
{
	char	fps_text[16];

	sprintf(fps_text, "FPS: %.0f", data->frames.fps);
	mlx_string_put(data->mlx, data->win, WIN_WIDTH - 100, 50, 0xFFFFFF,
		fps_text);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_util_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:28:01 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/25 18:28:01 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_textures(t_data *data)
{
	load_textures(data, &data->textures.north);
	load_textures(data, &data->textures.south);
	load_textures(data, &data->textures.east);
	load_textures(data, &data->textures.west);
}

void	init_game(t_data *data)
{
	data->ceiling.r = -1;
	data->ceiling.g = -1;
	data->ceiling.b = -1;
	data->floor.r = -1;
	data->floor.g = -1;
	data->floor.b = -1;
	data->player.dir.x = 1.0;
	data->player.dir.y = 1.0;
	data->player.plane.x = 1.0;
	data->player.plane.y = 0.66;
	data->frames.time = 0.0;
	data->frames.old_time = 0.0;
	data->move_speed = 1.0;
	data->global_light = lerp_day_cycle(data, data->time_of_day);
	data->time_of_day = 0.75;
	data->bsunrise = false;
	data->bsunset = false;
	data->bsun = false;
	data->bmoon = true;
}

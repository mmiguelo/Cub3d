/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:01:02 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/14 23:01:02 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	apply_global_brightness(int color, double global_light)
{
	int	rgb[3];

	rgb[0] = ((color >> 16) & 0xFF) * global_light;
	rgb[1] = ((color >> 8) & 0xFF) * global_light;
	rgb[2] = (color & 0xFF) * global_light;
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

int	apply_brightness(int color, double brightness)
{
	int	rgb[3];

	rgb[0] = ((color >> 16) & 0xFF) * brightness;
	rgb[1] = ((color >> 8) & 0xFF) * brightness;
	rgb[2] = (color & 0xFF) * brightness;
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	update_global_light(t_data *data)
{
	data->global_light += DAY_NIGHT_SPEED * data->light_direction;
	if (data->global_light <= 0.2)
	{
		data->global_light = 0.2;
		data->light_direction = 1;
	}
	else if (data->global_light >= 1.0)
	{
		data->global_light = 1.0;
		data->light_direction = -1;
	}
}

int	lerp_ceilling(int day_color, int night_color, double global_light)
{
	int	rgb[3];

	rgb[0] = ((day_color >> 16) & 0xFF) * global_light
		+ ((night_color >> 16) & 0xFF) * (1 - global_light);
	rgb[1] = ((day_color >> 8) & 0xFF) * global_light
		+ ((night_color >> 8) & 0xFF) * (1 - global_light);
	rgb[2] = (day_color & 0xFF) * global_light
		+ (night_color & 0xFF) * (1 - global_light);
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	if (rgb[0] < 0)
		rgb[0] = 0;
	if (rgb[1] < 0)
		rgb[1] = 0;
	if (rgb[2] < 0)
		rgb[2] = 0;
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

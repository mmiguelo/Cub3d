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

/**
 * update_global_light - Updates the global lighting intensity based
 * on the time of day.
 *
 * The function creates a smooth, continuous day-night cycle using cosine wave:
 *
 *    - At midnight (time_of_day = 0.0 or 1.0), the light is at its min (0.2).
 *    - At sunrise (time_of_day = 0.25), the light begins to increase.
 *    - At noon (time_of_day = 0.5), the light reaches its maximum (1.0).
 *    - At sunset (time_of_day = 0.75), the light decreases again.
 *    - The cycle loops back to midnight (time_of_day = 1.0).
 *
 * The cosine function ensures the transition is smooth and continuous,
 * without flat plateaus between phases (similar to games like Elden Ring).
 *
 * Formula:
 *      cycle = cos((time_of_day * 2?) - ?)   // gives values in [-1, 1]
 *      global_light = 0.2 + ((cycle + 1) / 2) * (1.0 - 0.2)
 *
 * Resulting global_light is always clamped to [0.2, 1.0].
 *
 * @param data Pointer to the main game data structure containing:
 * @param time_of_day : a double in range [0.0, 1.0)
 * @param global_light: the computed light intensity multiplier
 */
void	update_global_light(t_data *data)
{
	double	t;
	double	cycle;

	t = fmod(data->time_of_day, 1.0);
	cycle = cos((t * 2.0 * PI) - PI);
	if (data->player.sprint)
		data->global_light = 0.2 + ((cycle + 1.0) / 2.0) * (1.0 - 0.2);
	else

	if (data->global_light < 0.2)
		data->global_light = 0.2;
	if (data->global_light > 1.0)
		data->global_light = 1.0;
}

int	lerp_day_cycle(t_data *data, double day_cycle)
{
	day_cycle = fmod(day_cycle, 1.0);
	if (day_cycle < 0.25)
	{
		if (data->bmoon)
			change_day(&data->bmoon, &data->bsunrise);
		return (lerp_color(MORNING, NOON, day_cycle / 0.25));
	}
	else if (day_cycle < 0.5)
	{
		if (data->bsunrise)
			change_day(&data->bsunrise, &data->bsun);
		return (lerp_color(NOON, EVENING, (day_cycle - 0.25) / 0.25));
	}
	else if (day_cycle < 0.75)
	{
		if (data->bsun)
			change_day(&data->bsun, &data->bsunset);
		return (lerp_color(EVENING, NIGHT, (day_cycle - 0.5) / 0.25));
	}
	else
	{
		if (data->bsunset)
			change_day(&data->bsunset, &data->bmoon);
		return (lerp_color(NIGHT, MORNING, (day_cycle - 0.75) / 0.25));
	}
}

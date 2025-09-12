/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:39:47 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/09/12 14:04:51 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_flashlight_overlay(t_data *data)
{
	int		x;
	int		y;

	if (!data->fl_on)
		return ;
	data->fl.radius = 600;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			apply_flashlight_pixel(data, &data->fl, x, y);
		}
	}
}

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	toggle_flashlight(t_data *data)
{
	data->fl_on = !data->fl_on;
	if (data->fl_on)
	{
		data->fl.flicker_frames = 20 + rand() % 20;
		data->fl.flicker_factor = 1.0;
	}
	else
	{
		data->fl.flicker_frames = 0;
		data->fl.flicker_factor = 1.0;
	}
}

void	apply_flashlight_pixel(t_data *data, t_fl *flashlight, int x, int y)
{
	int	center_x;
	int	center_y;
	int	color;

	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	flashlight->position.x = x - center_x;
	flashlight->position.y = y - center_y;
	flashlight->dist = sqrt(flashlight->position.x * flashlight->position.x
			+ flashlight->position.y * flashlight->position.y);
	if (flashlight->dist < flashlight->radius)
	{
		color = get_pixel(&data->image, x, y);
		flashlight->factor = (2.5 - (flashlight->dist / flashlight->radius)
				* 1.8) * flashlight->flicker_factor;
		if (flashlight->factor < 1.0)
			flashlight->factor = 1.0;
		color = apply_brightness(color, flashlight->factor);
		draw_pixel(&data->image, x, y, color);
	}
}

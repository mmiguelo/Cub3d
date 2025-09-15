/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:25:32 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/09/15 19:23:57 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	lerp_day_cycle_fc(t_data *data, double day_cycle)
{
	day_cycle = fmod(day_cycle, 1.0);
	if (day_cycle < 0.25)
	{
		if (data->bmoon)
			change_day(&data->bmoon, &data->bsunrise);
	}
	else if (day_cycle < 0.5)
	{
		if (data->bsunrise)
			change_day(&data->bsunrise, &data->bsun);
	}
	else if (day_cycle < 0.75)
	{
		if (data->bsun)
			change_day(&data->bsun, &data->bsunset);
	}
	else
	{
		if (data->bsunset)
			change_day(&data->bsunset, &data->bmoon);
	}
}

void	init_fc_directions(t_data *data, t_fccast *fc)
{
	fc->dir0.x = data->player.dir.x - data->player.plane.x;
	fc->dir0.y = data->player.dir.y - data->player.plane.y;
	fc->dir1.x = data->player.dir.x + data->player.plane.x;
	fc->dir1.y = data->player.dir.y + data->player.plane.y;
	fc->pos_z = WIN_HEIGHT * 0.5;
	fc->horizon = fc->pos_z + (int)((data->player.height - 0.5) * WIN_HEIGHT);
}

void	calculate_text_coord(t_fccast *fc)
{
	fc->cell.x = (int)floor(fc->x);
	fc->cell.y = (int)floor(fc->y);
	fc->tex.x = fc->x - fc->cell.x;
	fc->tex.y = fc->y - fc->cell.y;
	if (fc->tex.x < 0.0)
		fc->tex.x += 1.0;
	if (fc->tex.y < 0.0)
		fc->tex.y += 1.0;
}

void	render_fc_row(t_data *data, t_fccast *fc, t_img *texture, int y)
{
	int				x;
	unsigned int	check;

	fc->x = data->player.x + fc->row_distance * fc->dir0.x;
	fc->y = data->player.y + fc->row_distance * fc->dir0.y;
	fc->step.x = fc->row_distance * (fc->dir1.x - fc->dir0.x) / WIN_WIDTH;
	fc->step.y = fc->row_distance * (fc->dir1.y - fc->dir0.y) / WIN_WIDTH;
	x = 0;
	while (x < WIN_WIDTH)
	{
		calculate_text_coord(fc);
		fc->temp.x = x;
		fc->temp.y = y;
		check = get_pixel(&data->image, fc->temp.x, fc->temp.y);
		if (check == BG)
			render_fc_pixel(data, fc, texture);
		fc->x += fc->step.x;
		fc->y += fc->step.y;
		x++;
	}
}

void	render_fc(t_data *data, t_fccast *fc)
{
	int	y;
	int	max_distance;
	int	i;

	init_fc_directions(data, fc);
	max_distance = WIN_HEIGHT - fc->horizon;
	if (fc->horizon > max_distance)
		max_distance = fc->horizon;
	i = 0;
	while (i < max_distance)
	{
		fc->row_distance = fc->pos_z / i;
		y = fc->horizon + i;
		if (y < WIN_HEIGHT)
			render_fc_row(data, fc, &data->textures.floor, y);
		y = fc->horizon - i - 1;
		if (y >= 0)
			render_fc_row(data, fc, &data->textures.ceiling, y);
		i++;
	}
	lerp_day_cycle_fc(data, data->time_of_day);
}

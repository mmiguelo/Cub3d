/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:00:37 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/13 13:00:37 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init(t_data *data)
{
	if (!data)
		ft_kill(NULL, ERR_MALLOC);
	ft_bzero(data, sizeof(t_data));
	init_game(data);
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
	data->time_of_day = 0.0;
	data->bsunrise = true;
	data->bsunset = false;
	data->bsun = false;
	data->bmoon = false;
}

void	init_image(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	data->bg.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->bg.addr = mlx_get_data_addr(data->bg.img,
			&data->bg.bpp, &data->bg.line_length, &data->bg.endian);
	data->bg.width = WIN_WIDTH;
	data->bg.height = WIN_HEIGHT;
	data->image.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->image.addr = mlx_get_data_addr(data->image.img,
			&data->image.bpp, &data->image.line_length,
			&data->image.endian);
	data->image.width = WIN_WIDTH;
	data->image.height = WIN_HEIGHT;
	init_cycle_images(data);
}

void	init_cycle_images(t_data *data)
{
	parse(data, "./textures/bonus/sun.xpm", ".xpm");
	data->sun.img = mlx_xpm_file_to_image(data->mlx, "./textures/bonus/sun.xpm",
			&data->sun.width, &data->sun.height);
	data->sun.addr = mlx_get_data_addr(data->sun.img,
			&data->sun.bpp, &data->sun.line_length, &data->sun.endian);
	parse(data, "./textures/bonus/moon.xpm", ".xpm");
	data->moon.img = mlx_xpm_file_to_image(data->mlx,
			"./textures/bonus/moon.xpm", &data->moon.width, &data->moon.height);
	data->moon.addr = mlx_get_data_addr(data->moon.img,
			&data->moon.bpp, &data->moon.line_length,
			&data->moon.endian);
	parse(data, "./textures/bonus/sunrise.xpm", ".xpm");
	data->sunrise.img = mlx_xpm_file_to_image(data->mlx,
			"./textures/bonus/sunrise.xpm", &data->sunrise.width,
			&data->sunrise.height);
	data->sunrise.addr = mlx_get_data_addr(data->sunrise.img,
			&data->sunrise.bpp, &data->sunrise.line_length,
			&data->sunrise.endian);
	parse(data, "./textures/bonus/sunset.xpm", ".xpm");
	data->sunset.img = mlx_xpm_file_to_image(data->mlx,
			"./textures/bonus/sunset.xpm", &data->sunset.width,
			&data->sunset.height);
	data->sunset.addr = mlx_get_data_addr(data->sunset.img,
			&data->sunset.bpp, &data->sunset.line_length,
			&data->sunset.endian);
}

void	load_textures(t_data *data, t_img *texture)
{
	texture->img = mlx_xpm_file_to_image(data->mlx,
			texture->path, &texture->width, &texture->height);
	if (!texture->img)
		ft_kill(data, ERR_TEX_LOAD);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
		ft_kill(data, ERR_TEX_LOAD);
}

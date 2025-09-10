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

void	init_image(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	data->image.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->image.addr = mlx_get_data_addr(data->image.img,
			&data->image.bpp, &data->image.line_length,
			&data->image.endian);
	data->image.width = WIN_WIDTH;
	data->image.height = WIN_HEIGHT;
	init_cycle_images(data);
	init_door_image(data);
}

void	init_cycle_images(t_data *data)
{
	parse(data, "./textures/bonus/sun.xpm", ".xpm");
	data->sun.img = mlx_xpm_file_to_image(data->mlx,
			"./textures/bonus/sun.xpm", &data->sun.width, &data->sun.height);
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

void	init_door_image(t_data *data)
{
	parse(data, "./textures/bonus/RD_WB_spritesheet.xpm", ".xpm");
	data->door_spritesheet.img = mlx_xpm_file_to_image(data->mlx,
			"./textures/bonus/RD_WB_spritesheet.xpm", &data->door_spritesheet.width,
			&data->door_spritesheet.height);
	data->door_spritesheet.addr = mlx_get_data_addr(data->door_spritesheet.img,
			&data->door_spritesheet.bpp, &data->door_spritesheet.line_length,
			&data->door_spritesheet.endian);
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

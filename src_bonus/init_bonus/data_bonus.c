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

void	init_bonus_image(t_data *data, t_img *texture, char *path)
{
	parse(data, path, ".xpm");
	texture->img = mlx_xpm_file_to_image(data->mlx,
			path, &texture->width, &texture->height);
	if (!texture->img)
		ft_kill(data, ERR_TEX_LOAD);
	texture->addr = mlx_get_data_addr(texture->img ,
			&texture->bpp, &texture->line_length, &texture->endian);
	if (!texture->addr)
		ft_kill(data, ERR_TEX_LOAD);
}

void	init_cycle_images(t_data *data)
{
	init_bonus_image(data, &data->sun, "./textures/bonus/sun.xpm");
	init_bonus_image(data, &data->moon, "./textures/bonus/moon.xpm");
	init_bonus_image(data, &data->sunrise, "./textures/bonus/sunrise.xpm");
	init_bonus_image(data, &data->sunset, "./textures/bonus/sunset.xpm");
	init_bonus_image(data,
		&data->door_spritesheet, "./textures/bonus/RD_WB_spritesheet.xpm");
	init_bonus_image(data, &data->textures.ceiling, IMG_CELING);
	init_bonus_image(data, &data->textures.floor, IMG_FLOOR);
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

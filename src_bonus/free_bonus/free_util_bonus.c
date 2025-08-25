/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:53:50 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/25 16:53:50 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	destroy_images(t_data *data)
{
	if (data->textures.east.img)
		mlx_destroy_image(data->mlx, data->textures.east.img);
	if (data->textures.west.img)
		mlx_destroy_image(data->mlx, data->textures.west.img);
	if (data->textures.south.img)
		mlx_destroy_image(data->mlx, data->textures.south.img);
	if (data->textures.north.img)
		mlx_destroy_image(data->mlx, data->textures.north.img);
	if (data->bg.img)
		mlx_destroy_image(data->mlx, data->bg.img);
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	if (data->sun.img)
		mlx_destroy_image(data->mlx, data->sun.img);
	if (data->sunrise.img)
		mlx_destroy_image(data->mlx, data->sunrise.img);
	if (data->sunset.img)
		mlx_destroy_image(data->mlx, data->sunset.img);
	if (data->moon.img)
		mlx_destroy_image(data->mlx, data->moon.img);
}

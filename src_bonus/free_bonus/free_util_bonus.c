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

void	image_destroyer(t_data *data, t_img *texture)
{
	if (texture->img)
	{
		mlx_destroy_image(data->mlx, texture->img);
		texture->img = NULL;
	}
}

void	destroy_images(t_data *data)
{
	image_destroyer(data, &data->textures.east);
	image_destroyer(data, &data->textures.east);
	image_destroyer(data, &data->textures.west);
	image_destroyer(data, &data->textures.south);
	image_destroyer(data, &data->textures.north);
	image_destroyer(data, &data->image);
	image_destroyer(data, &data->sun);
	image_destroyer(data, &data->sunrise);
	image_destroyer(data, &data->sunset);
	image_destroyer(data, &data->moon);
	image_destroyer(data, &data->door_spritesheet);
	image_destroyer(data, &data->textures.ceiling);
	image_destroyer(data, &data->textures.floor);
}

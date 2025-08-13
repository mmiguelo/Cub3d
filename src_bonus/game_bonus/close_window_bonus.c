/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:01:05 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/13 14:29:44 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	free_tex(t_img *tex, void *mlx)
{
	if (tex->img)
	{
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
	}
}

void	destroy_textures(t_textures *textures, void *mlx)
{
	if (!textures || !mlx)
		return ;
	if (textures->north.img)
		free_tex(&textures->north, mlx);
	if (textures->south.img)
		free_tex(&textures->south, mlx);
	if (textures->east.img)
		free_tex(&textures->east, mlx);
	if (textures->west.img)
		free_tex(&textures->west, mlx);
}

void	close_window(t_data *data, char *msg)
{
	if (!msg)
		msg = GAME_ENDED;
	ft_kill(data, msg);
}

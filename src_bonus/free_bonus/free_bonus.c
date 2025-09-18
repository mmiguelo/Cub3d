/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:59:59 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/09/17 09:51:13 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	free_images(t_data *data)
{
	if (data && data->mlx)
	{
		destroy_images(data);
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}

void	free_textures(t_data *data)
{
	if (data->textures.north.path)
		free(data->textures.north.path);
	if (data->textures.south.path)
		free(data->textures.south.path);
	if (data->textures.west.path)
		free(data->textures.west.path);
	if (data->textures.east.path)
		free(data->textures.east.path);
}

void	freedom(t_data *data)
{
	int	i;

	if (data && data->map.grid)
	{
		i = -1;
		while (data->map.grid[++i])
			free(data->map.grid[i]);
		free(data->map.grid);
		data->map.grid = NULL;
	}
	free_textures(data);
	destroy_textures(&data->textures, data->mlx);
	free_images(data);
	data->mlx = NULL;
}

void	free_gnl(t_data *data)
{
	if (!data->line)
		return ;
	while (data->line)
	{
		free(data->line);
		data->line = get_next_line(data->fd);
	}
}

int	ft_kill(t_data *data, char *msg)
{
	if (ft_strcmp(msg, ERR_EMPTY) != 0)
		free_gnl(data);
	if (data)
		freedom(data);
	if (ft_strcmp(msg, GAME_ENDED) == 0)
		ft_printf_fd(1, G"\nCongratulations\n\n"RST);
	else
		ft_printf_fd(2, RED"Error\n%s"RST, msg);
	exit(EXIT_FAILURE);
}

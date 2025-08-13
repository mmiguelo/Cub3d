/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:01:12 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/13 14:29:54 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	print_assets(t_data *data, char *process)
{
	ft_printf("\n\n%s:\n", process);
	ft_printf("NO: '%s'\n", data->textures.north.path);
	ft_printf("SO: '%s'\n", data->textures.south.path);
	ft_printf("WE: '%s'\n", data->textures.west.path);
	ft_printf("EA: '%s'\n", data->textures.east.path);
	ft_printf("Floor->R: '%d'\n", data->floor.r);
	ft_printf("Floor->G: '%d'\n", data->floor.g);
	ft_printf("Floor->B: '%d'\n", data->floor.b);
	ft_printf("Ceiling->R: '%d'\n", data->ceiling.r);
	ft_printf("Ceiling->G: '%d'\n", data->ceiling.g);
	ft_printf("Ceiling->B: '%d'", data->ceiling.b);
}

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	ft_printf_fd(1, Y"\n\nMAP:\n\n"RST);
	while (data->map.grid[i])
	{
		ft_printf_fd(1, "len:%d			'%s'\n", ft_strlen(data->map.grid[i]),
			data->map.grid[i]);
		i++;
	}
	ft_printf("height: %d\n", data->map.height);
	ft_printf("width: %d\n", data->map.width);
	ft_printf("Direction of player: %c\n\n\n", data->map.direction);
	ft_printf("player postion: x-> %f y-> %f", data->player.x, data->player.y);
}

void	print_parsing_map(t_data *data, int y)
{
	if (y < 10)
		ft_printf("grid[0%d] : %s\n", y, data->map.grid[y]);
	else
		ft_printf("grid[%d] : %s\n", y, data->map.grid[y]);
}

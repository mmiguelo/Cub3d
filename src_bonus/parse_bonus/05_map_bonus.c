/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_map_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:00:15 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/10/09 14:18:46 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	check_map(t_data *data, t_map	*map, char *line, int height)
{
	int	width;

	width = 0;
	parse_line(data, line);
	if (!is_valid_map_line(line))
		ft_kill(data, ERR_MAP);
	map->started = true;
	map->height = height + 1;
	if (is_valid_map_line(line) && map->ended)
		ft_kill(data, ERR_MAP);
	if (!map->ended)
	{
		width = count_width(line);
		if (width > map->width)
			map->width = width;
		append_map_line(data, &map->grid, line, height);
	}
}

void	append_map_line(t_data *data, char ***grid, char *line, int height)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (height + 2));
	if (!new_grid)
		ft_kill(data, ERR_MALLOC);
	i = 0;
	while (i < height && *grid)
	{
		new_grid[i] = (*grid)[i];
		i++;
	}
	new_grid[i] = clean_ws(data, line);
	if (!new_grid[i])
		ft_kill(data, ERR_MALLOC);
	new_grid[i + 1] = NULL;
	free(*grid);
	*grid = new_grid;
}

void	check_map_walls_and_player(t_data *data, t_map *map)
{
	int	x;
	int	y;

	y = -1;
	if (!map->started)
		ft_kill(data, ERR_ORDER);
	while (++y < map->height)
	{
		x = -1;
		while (++x < (int)(ft_strlen(map->grid[y])))
		{
			if (map->grid[y][x] == '0' || ft_strchr("NSEWDdn", map->grid[y][x]))
				check_surroundings(data, map->grid, x, y);
			else if (map->grid[y][x] == '1' || ft_strchr(WS, map->grid[y][x]))
				continue ;
			else
				ft_kill(data, "Invalid map character\n");
		}
	}
	if (!map->direction)
		ft_kill(data, ERR_PLAYER);
}

void	check_surroundings(t_data *data, char **grid, int x, int y)
{
	if (ft_strchr("NSEW", data->map.grid[y][x]))
	{
		if (data->map.direction)
			ft_kill(data, "Map must have only one player\n");
		data->map.direction = grid[y][x];
		data->player.x = x + 0.5;
		data->player.y = y + 0.5;
	}
	if (y == 0 || !grid[y - 1] || x >= (int)ft_strlen(grid[y - 1])
		|| ft_strchr(WS, grid[y - 1][x]))
		ft_kill(data, ERR_MAP);
	if (!grid[y + 1] || x >= (int)ft_strlen(grid[y + 1])
		|| ft_strchr(WS, grid[y + 1][x]))
		ft_kill(data, ERR_MAP);
	if (x == 0 || !grid[y] || ft_strchr(WS, grid[y][x - 1]))
		ft_kill(data, ERR_MAP);
	if (x + 1 >= (int)ft_strlen(grid[y]) || ft_strchr(WS, grid[y][x + 1]))
		ft_kill(data, ERR_MAP);
	if (ft_strchr("Ddn", grid[y][x]))
		parse_door(data, x, y);
}

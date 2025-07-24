#include "cub3D.h"

bool	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (!ft_strchr(WS, line[i]) && !ft_strchr(VALID_MAP_CHARS, line[i]))
			return (false);
		i++;
	}
	return (true);
}

void	check_map(t_data *data, t_map	*map, char *line, int height)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
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

/* void	check_map2(t_data *data, t_map	*map, char *line, int height)
{
	while (line = get_next_line(fd) != NULL)
	{
		if (ft_has_white_spaces(line))
		
	}
	
} */

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
	new_grid[i] = ft_strdup(line);
	if (!new_grid[i])
		ft_kill(data, ERR_MALLOC);
	new_grid[i + 1] = NULL;
	free(*grid);
	*grid = new_grid;
}

int	count_width(const char *str)
{
	int	i;

	i = 0;
	while (!(ft_has_white_spaces((char *)(str + i))))
		i++;
	/* while (str[i] != '\n' && str[i] != '\r' && str[i] != '\0')
		i++; */
	return (i);
}

/* void check_map_walls(t_data *data, t_map *map)
{
	int	x;	int width;
	int	y;

	y = 0;
	while (y <= map->height)
	{
		x = 0;
		while (x <= map->width)
		{
			if (map->grid[y][x] == '0')
			{
				
			}
		}

	}
	

}

void check_player_position */

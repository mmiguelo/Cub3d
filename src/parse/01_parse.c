#include "cub3D.h"

void	parse(char *filename)
{
	if (access(filename, F_OK | W_OK) == -1)
		ft_kill(NULL, ERR_FILE);
	check_directory(filename);
	check_extension(filename, ".cub");
	check_redability(filename);
}

void	check_assets(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && ft_isspace(line[i + 2]))
		assign_texture(data, &data->textures.north.path, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2]))
		assign_texture(data, &data->textures.south.path, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2]))
		assign_texture(data, &data->textures.west.path, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2]))
		assign_texture(data, &data->textures.east.path, line, &i);
	else if (line[i] == 'F' && ft_isspace(line[i + 1]))
		assign_rgb(data, &data->floor, line, &i);
	else if (line[i] == 'C' && ft_isspace(line[i + 1]))
		assign_rgb(data, &data->ceiling, line, &i);
}

void	parse_file_content(t_data *data, char *filename)
{
	int		fd;
	char	*line;
	int	i;

	i = -1;
	fd = open(filename, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_has_white_spaces(line))
		{
			if (data->map.started)
				data->map.ended = true;
			free(line);
			continue ;
		}
		if (is_all_assets(data))
			check_map(data, &data->map, line, ++i);
		else
			check_assets(data, line);
		free(line);
	}
	check_map_walls_and_player(data, &data->map);
	/* check_player_position(data, ); */
	check_required_textures(data, &data->textures);
	check_duplicated_color(data, &data->ceiling, &data->floor);
	print_assets(data, "After assigning");
	print_map(data);
}

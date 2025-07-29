#include "cub3D.h"

bool	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(WS, line[i]) && !ft_strchr(VALID_MAP_CHARS, line[i]))
			return (false);
		i++;
	}
	return (true);
}

char	*clean_ws(t_data *data, char *line)
{
	char	*new_line;
	int		width;

	width = count_width(line);
	new_line = ft_calloc((size_t)(width + 1), sizeof(char));
	if (!new_line)
		ft_kill(data, ERR_MALLOC);
	ft_strlcpy(new_line, line, (size_t)width + 1);
	return (new_line);
}

int	count_width(const char *str)
{
	int	i;

	i = 0;
	while (!(ft_has_white_spaces((char *)(str + i))))
		i++;
	return (i);
}

void	parse_line(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && ft_isspace(line[i + 2])
		&& data->textures.north.path)
		ft_kill(data, ERR_DUPLICATION);
	else if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2])
		&& data->textures.south.path)
		ft_kill(data, ERR_DUPLICATION);
	else if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2])
		&& data->textures.west.path)
		ft_kill(data, ERR_DUPLICATION);
	else if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2])
		&& data->textures.east.path)
		ft_kill(data, ERR_DUPLICATION);
	else if (line[i] == 'F' && ft_isspace(line[i + 1])
		&& is_already_rgb(&data->floor))
		ft_kill(data, ERR_DUPLICATION);
	else if (line[i] == 'C' && ft_isspace(line[i + 1])
		&& is_already_rgb(&data->ceiling))
		ft_kill(data, ERR_DUPLICATION);
}

bool	is_already_rgb(t_color *color)
{
	return (color->r != -1 || color->g != -1 || color->b != -1);
}

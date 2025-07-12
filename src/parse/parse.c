#include "cub3D.h"

void	parse(char *filename)
{
	if (access(filename, F_OK | W_OK) == -1)
		ft_kill(NULL, ERR_FILE);
	check_directory(filename);
	check_extension(filename, ".cub");
	check_redability(filename);
}

void	parse_file_content(t_data *data, char *filename)
{
	int	fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		check_textures(data, line);
		free(line);
		line = get_next_line(fd);
	}
	check_duplicated_textures(&data->textures);
	check_duplicated_color(data, &data->ceiling, &data->floor);
	ft_printf_fd(1, "NO: %s\n", data->textures.north.path);
	ft_printf_fd(1, "SO: %s\n", data->textures.south.path);
	ft_printf_fd(1, "WE: %s\n", data->textures.west.path);
	ft_printf_fd(1, "EA: %s\n", data->textures.east.path);
	ft_printf_fd(1, "Floor: %d, %d, %d\n", data->floor.r, data->floor.g, data->floor.b);
	ft_printf_fd(1, "Ceiling: %d, %d, %d\n", data->ceiling.r, data->ceiling.g, data->ceiling.b);
}

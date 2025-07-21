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
	print_assets(data, "Before assigning");
	while (line)
	{
		check_textures(data, line);
		free(line);
		line = get_next_line(fd);
	}
	check_required_textures(data, &data->textures);
	check_duplicated_color(data, &data->ceiling, &data->floor);
	print_assets(data, "After assigning");
}

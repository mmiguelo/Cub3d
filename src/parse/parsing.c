#include "cub3D.h"

void	parse(char *filename)
{
	if (access(filename, F_OK | W_OK) == -1)
		ft_kill(NULL, ERR_FILE);
	check_directory(filename);
	check_extension(filename);
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
		if (!check_textures(line, data))
			break ;
	}
}
/* 
if ((line[i] == 'N' && line[i + 1] == 'O'))
	insert_north

else if (line[i] == 'S' && line[i + 1] == 'O')
else if (line[i] == 'W' && line[i + 1] == 'E')
else if (line[i] == 'S' && line[i + 1] == 'E')
else if (line[i] == 'F' && line[i + 1] == ' ')
else if (line[i] == 'C' && line[i + 1] == ' ') */
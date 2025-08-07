#include "cub3D.h"

void	check_directory(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		ft_kill(data, ERR_DIRECTORY);
	}
}

void	check_extension(t_data *data, char *filename, char *extension)
{
	int	len;

	len = ft_strlen(filename);
	if (ft_strlen(filename) <= 4)
		ft_kill(data, ERR_NAME);
	else if (filename[len - 5] == '/')
		ft_kill(data, ERR_FILE);
	else if (ft_strncmp(filename + len - 4, extension, 4) != 0)
	{
		if (ft_strncmp(extension, ".cub", 4) == 0)
			ft_kill(data, ERR_EXTENSION_FILE);
		else if (ft_strncmp(extension, ".xpm", 4) == 0)
			ft_kill(data, ERR_EXTENSION_TEXTURE);
	}
}

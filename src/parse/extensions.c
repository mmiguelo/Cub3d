#include "../../includes/cub3D.h"

void	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (ft_strlen(filename) <= 4)
		error_msg(ERR_NAME);
	else if (filename[len - 5] == '/')
		error_msg(ERR_FILE);
	else if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		error_msg(ERR_EXTENSION);
}

void	check_directory(char *filename)
{
	int	fd;

	fd = open(filename, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		error_msg(ERR_DIRECTORY);
	}
	close(fd);
}

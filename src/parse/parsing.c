#include "cub3D.h"

int	check_extension(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (ft_strlen(filename) <= 4)
		return (1);
	else if (filename[len - 5] == '/')
		return (1);
	else if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (1);
	return (0);
}

int	check_directory(char *filename)
{
	int	fd;

	fd = open(filename, __O_DIRECTORY);
	if (fd < 0)
		return (0);
	else
	{
		error_msg("Map sent is a directory!");
		exit (0);
	}
}

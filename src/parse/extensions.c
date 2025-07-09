#include "cub3D.h"

void	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (ft_strlen(filename) <= 4)
		ft_kill(NULL, ERR_NAME);
	else if (filename[len - 5] == '/')
		ft_kill(NULL, ERR_FILE);
	else if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		ft_kill(NULL, ERR_EXTENSION);
}

void	check_directory(char *filename)
{
	int	fd;

	fd = open(filename, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		ft_kill(NULL, ERR_DIRECTORY);
	}
	close(fd);
}

void	check_redability(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		ft_kill(NULL, ERR_FILE);
	}
	close(fd);
}

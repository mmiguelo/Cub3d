#include "cub3D.h"

void	parse(char *filename)
{
	if (access(filename, F_OK | W_OK) == -1)
		error_msg(ERR_FILE);
	check_directory(filename);
	check_extension(filename);
}

#include "cub3D.h"

void	print_assets(t_data *data, char *process)
{
	ft_printf_fd(1, "\n\n%s:\n", process);
	ft_printf_fd(1, "NO: %s\n", data->textures.north.path);
	ft_printf_fd(1, "SO: %s\n", data->textures.south.path);
	ft_printf_fd(1, "WE: %s\n", data->textures.west.path);
	ft_printf_fd(1, "EA: %s\n", data->textures.east.path);
	ft_printf_fd(1, "Floor->R: %d\n", data->floor.r);
	ft_printf_fd(1, "Floor->G: %d\n", data->floor.g);
	ft_printf_fd(1, "Floor->B: %d\n", data->floor.b);
	ft_printf_fd(1, "Ceiling->R: %d\n", data->ceiling.r);
	ft_printf_fd(1, "Ceiling->G: %d\n", data->ceiling.g);
	ft_printf_fd(1, "Ceiling->B: %d\n", data->ceiling.b);
}

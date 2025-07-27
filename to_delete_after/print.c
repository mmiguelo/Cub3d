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
	ft_printf_fd(1, "Ceiling->B: %d", data->ceiling.b);
}

void print_map(t_data *data)
{
	int i = 0;

	ft_printf_fd(1, Y"\n\nMAP:\n\n"RST);
	while(data->map.grid[i])
	{
		ft_printf_fd(1, "len:%d			%s\n", ft_strlen(data->map.grid[i]), data->map.grid[i]);
		i++;
	}
	ft_printf_fd(1, "height: %d\n", data->map.height);
	ft_printf_fd(1, "width: %d\n", data->map.width);
	ft_printf_fd(1, "Direction of player: %c\n\n\n", data->map.direction);
}

void print_parsing_map(t_data *data, int y)
{
	if (y < 10)
		printf("grid[0%d] : %s\n", y, data->map.grid[y]);
	else
		printf("grid[%d] : %s\n", y, data->map.grid[y]);
}

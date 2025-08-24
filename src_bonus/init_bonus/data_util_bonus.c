#include "cub3D_bonus.h"

void	init_cycle_images(t_data *data)
{
	data->sun.img = mlx_xpm_file_to_image(data->mlx, "./textures/bonus/sun.xpm",
			&data->sun.width, &data->sun.height);
	data->sun.addr = mlx_get_data_addr(data->sun.img,
		&data->sun.bits_per_pixel, &data->sun.line_length, &data->sun.endian);
	data->moon.img = mlx_xpm_file_to_image(data->mlx,
			"./textures/bonus/moon.xpm", &data->moon.width, &data->moon.height);
	data->moon.addr = mlx_get_data_addr(data->moon.img,
			&data->moon.bits_per_pixel, &data->moon.line_length,
			&data->moon.endian);
	data->sunrise.img = mlx_xpm_file_to_image(data->mlx,
			"./textures/bonus/sunrise.xpm", &data->sunrise.width,
			&data->sunrise.height);
	data->sunrise.addr = mlx_get_data_addr(data->sunrise.img,
		&data->sunrise.bits_per_pixel, &data->sunrise.line_length,
		&data->sunrise.endian);
	data->sunset.img = mlx_xpm_file_to_image(data->mlx,
		"./textures/bonus/sunset.xpm", &data->sunset.width,
		&data->sunset.height);
	data->sunset.addr = mlx_get_data_addr(data->sunset.img,
		&data->sunset.bits_per_pixel, &data->sunset.line_length,
		&data->sunset.endian);
}

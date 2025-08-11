#include "cub3D.h"

void	init(t_data *data)
{
	if (!data)
		ft_kill(NULL, ERR_MALLOC);
	ft_bzero(data, sizeof(t_data));
	init_game(data);
	init_image(data);
}

void	init_game(t_data *data)
{
	data->ceiling.r = -1;
	data->ceiling.g = -1;
	data->ceiling.b = -1;
	data->floor.r = -1;
	data->floor.g = -1;
	data->floor.b = -1;
	data->player.dir.x = 1.0;
	data->player.dir.y = 1.0;
	data->player.plane.x = 1.0;
	data->player.plane.y = 0.66;
	data->frames.time = 0.0;
	data->frames.old_time = 0.0;
	data->move_speed = 1;
}

void	init_image(t_data *data)
{
	data->mlx = mlx_init();
	data->bg.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->bg.addr = mlx_get_data_addr(data->bg.img,
			&data->bg.bits_per_pixel, &data->bg.line_length, &data->bg.endian);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
}

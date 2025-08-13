#include "cub3D.h"

void	game_loop(t_data *data)
{
	init_image(data);
	init_textures(data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, x_press, data);
	mlx_loop_hook(data->mlx, &draw_loop, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_hook_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_hook_release, data);
	mlx_loop(data->mlx);
}

int	draw_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	calculate_movements(&data->player, data->map.grid);
	calculate_raycasting(data);
	return (0);
}

void	get_player_vector(t_data *data)
{
	if (data->map.direction == 'N')
	{
		data->player.dir.x = 0;
		data->player.dir.y = -1;
		data->player.plane.x = PLANE_LEN;
		data->player.plane.y = 0;
	}
	if (data->map.direction == 'S')
	{
		data->player.dir.x = 0;
		data->player.dir.y = 1;
		data->player.plane.x = -PLANE_LEN;
		data->player.plane.y = 0;
	}
	get_player_vector2(data);
}

void	get_player_vector2(t_data *data)
{
	if (data->map.direction == 'W')
	{
		data->player.dir.x = -1;
		data->player.dir.y = 0;
		data->player.plane.x = 0;
		data->player.plane.y = -PLANE_LEN;
	}
	if (data->map.direction == 'E')
	{
		data->player.dir.x = 1;
		data->player.dir.y = 0;
		data->player.plane.x = 0;
		data->player.plane.y = PLANE_LEN;
	}
}

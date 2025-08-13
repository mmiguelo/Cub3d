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

int	draw_loop(t_data *data)
{
	calculate_movements(data);
	calculate_raycasting(data);
	return (0);
}

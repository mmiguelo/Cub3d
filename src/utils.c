#include "cub3D.h"

void	free_images(t_data *data)
{
	if (data && data->mlx)
	{
		mlx_destroy_image(data->mlx, data->textures.east.img);
		mlx_destroy_image(data->mlx, data->textures.west.img);
		mlx_destroy_image(data->mlx, data->textures.south.img);
		mlx_destroy_image(data->mlx, data->textures.north.img);
		mlx_destroy_image(data->mlx, data->bg.img);
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
	}
}

void	free_textures(t_data *data)
{
	if (data->textures.north.path)
		free(data->textures.north.path);
	if (data->textures.south.path)
		free(data->textures.south.path);
	if (data->textures.west.path)
		free(data->textures.west.path);
	if (data->textures.east.path)
		free(data->textures.east.path);
}

void	freedom(t_data *data)
{
	int	i;

	if (data && data->map.grid)
	{
		i = -1;
		while (data->map.grid[++i])
			free(data->map.grid[i]);
		free(data->map.grid);
		data->map.grid = NULL;
	}
	free_textures(data);
	free_images(data);
	destroy_textures(&data->textures, data->mlx);
	if (data->mlx)
	{
		free(data->mlx);
		data->mlx = NULL;
	}
}

int	ft_kill(t_data *data, char *msg)
{
	if (data)
		freedom(data);
	if (ft_strcmp(msg, GAME_ENDED) == 0)
		ft_printf_fd(1, G"\nCongratulations\n\n"RST);
	else
		ft_printf_fd(2, RED"Error\n%s"RST, msg);
	exit(EXIT_FAILURE);
}

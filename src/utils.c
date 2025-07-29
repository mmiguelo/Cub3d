#include "cub3D.h"

void	free_textures(t_textures *textures)
{
	if (textures)
	{
		if (textures->north.path)
			free(textures->north.path);
		if (textures->south.path)
			free(textures->south.path);
		if (textures->west.path)
			free(textures->west.path);
		if (textures->east.path)
			free(textures->east.path);
	}
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
	free_textures(&data->textures);
	//TODO: free images
}

int	ft_kill(t_data *data, char *msg)
{
	if (data)
	{
		freedom(data);
		free(data);
	}
	if (ft_strcmp(msg, GAME_ENDED) == 0)
		ft_printf_fd(1, G"\nCongratulations\n\n"RST);
	else
		ft_printf_fd(2, RED"Error\n%s"RST, msg);
	exit(EXIT_FAILURE);
}

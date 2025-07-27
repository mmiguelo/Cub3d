#include "cub3D.h"

/* const char	*message(t_error_code i)
{
	const char	*message[14];

	message[0] = "Arguments are invalid\n";
	message[1] = "File must be *.cub\n";
	message[2] = "Extension must be .cub\n";
	message[3] = "EXtension must be .xpm\n";
	message[4] = "File is invalid or no permissions\n";
	message[5] = "Map is invalid\n";
	message[6] = "Map sent is a directory\n";
	message[7] = "Malloc failed\n";
	message[8] = "Color is invalid\n";
	message[9] = "Texture is invalid\n";
	message[10] = "MLX failed\n";
	message[11] = "Order is invalid\n";
	message[12] = "Duplication found\n";
	message[13] = "Game Ended\n";
	return (message[i]);
} */

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

/* int	ft_kill(t_data *data, t_error_code code)
{
	(void) data;
	if (data)
	{
		freedom(data);
		free(data);
	}
	if (code == GAME_ENDED)
		ft_printf_fd(2, G"Game Ended\n"RST);
	else if (code >= 0 && code <= 13)
		ft_printf_fd(2, RED"Error\n%s\n"RST, message(code));
	exit(EXIT_FAILURE);
} */

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
		ft_printf_fd(2, RED"Error\n%s\n"RST, msg);
	exit(EXIT_FAILURE);
}

#include "cub3D.h"

void	free_tex(t_img *tex, void *mlx)
{
	if (tex->img)
	{
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
	}
}

void	destroy_textures(t_textures *textures, void *mlx)
{
	free_tex(&textures->north, mlx);
	free_tex(&textures->south, mlx);
	free_tex(&textures->east, mlx);
	free_tex(&textures->west, mlx);
}

void	close_window(t_data *data, char *msg)
{
	if (!msg)
		msg = GAME_ENDED;
	ft_kill(data, msg);
}

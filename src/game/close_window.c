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
	if (!textures || !mlx)
		return;
	if (textures->north.img)
		free_tex(&textures->north, mlx);
	if (textures->south.img)
		free_tex(&textures->south, mlx);
	if (textures->east.img)
		free_tex(&textures->east, mlx);
	if (textures->west.img)
		free_tex(&textures->west, mlx);
}

void	close_window(t_data *data, char *msg)
{
	if (!msg)
		msg = GAME_ENDED;
	ft_kill(data, msg);
}

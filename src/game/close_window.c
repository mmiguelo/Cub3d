#include "cub3D.h"

/**
 * @brief Frees a single texture image from memory if allocated.
 *
 * @param tex Pointer to the texture structure containing the image.
 * @param mlx MLX instance pointer used to destroy the image.
 */
void	free_tex(t_tex *tex, void *mlx)
{
	if (tex->img)
	{
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
	}
}

/**
 * @brief Frees all texture images (north, south, east, west).
 *
 * @param textures Pointer to the texture group structure.
 * @param mlx	   MLX instance used to free the textures.
 */
void	destroy_textures(t_textures *textures, void *mlx)
{
	free_tex(&textures->north, mlx);
	free_tex(&textures->south, mlx);
	free_tex(&textures->east, mlx);
	free_tex(&textures->west, mlx);
}

int	close_window(t_data *data, char *msg)
{
	if (!msg)
		msg = GAME_ENDED;
	return (ft_kill(data, msg));
}

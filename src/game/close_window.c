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

/**
 * @brief Closes the game window, frees MLX and texture memory, and exits.
 *
 * @param data Pointer to the main game state structure.
 * @param msg  Optional message shown before exiting.
 *
 * @return Always returns -1 for convenience in error returns.
 */
int	close_window(t_data *data, char *msg)
{
	destroy_textures(&data->textures, data->mlx);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (!msg)
		msg = GAME_ENDED;
	ft_kill(data, msg);
	return (-1);
}
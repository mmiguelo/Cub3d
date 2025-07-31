#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3D.h"

void	open_window(t_data *data);
void	load_textures(t_data *data);
void	calculate_tile_size(t_data *data);
void	fill_image_with_color(void *img, void *mlx, int tile_size, int color);

#endif
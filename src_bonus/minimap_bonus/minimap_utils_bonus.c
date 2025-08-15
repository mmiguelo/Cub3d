#include "cub3D_bonus.h"

void	init_minimap(t_data *data)
{
	calculate_tile_size(data);
	data->minimap.floor_color = 0x000000;
	data->minimap.wall_color = 0xFFFFFF;
	data->minimap.player_color = 0x00FF00;
}


void	calculate_tile_size(t_data *data)
{
	int	max_width;
	int	max_height;
	int	tile_w;
	int	tile_h;

	max_width = WIN_WIDTH / 4;
	max_height = WIN_HEIGHT / 4;
	tile_w = max_width / data->map.width;
	tile_h = max_height / data->map.height;
	if (tile_w < tile_h)
		data->minimap.tile_size = tile_w;
	else
		data->minimap.tile_size = tile_h;
	if (data->minimap.tile_size < 2)
		data->minimap.tile_size = 2;
}

void clear_image(t_img *img, int color)
{
    int x, y;
    for (y = 0; y < img->height; y++)
        for (x = 0; x < img->width; x++)
            my_mlx_pixel_put(img, x, y, color);
}

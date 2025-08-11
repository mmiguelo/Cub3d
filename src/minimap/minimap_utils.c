#include "cub3D.h"

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

#include "cub3D.h"

void	fill_image_with_color(void *img, void *mlx, int tile_size, int color)
{
	int		*pixel;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		x;
	int		y;

	y = 0;
	addr = mlx_get_data_addr(img, &bpp, &ll, &endian);
	pixel = (int *)addr;
	while (y < tile_size)
	{
		x = 0;
		while (x < tile_size)
		{
			pixel[y * (ll / 4) + x] = color;
			x++;
		}
		y++;
	}
}

void load_textures(t_data *data)
{
	data->minimap.floor = mlx_new_image(data->mlx, data->minimap.tile_size, data->minimap.tile_size);
	if (!data->minimap.floor)
		ft_kill(data, "Error loading floor texture");
	fill_image_with_color(data->minimap.floor, data->mlx, data->minimap.tile_size, 0x000000);

	data->minimap.wall = mlx_new_image(data->mlx, data->minimap.tile_size, data->minimap.tile_size);
	if (!data->minimap.wall)
		ft_kill(data, "Error loading wall texture");
	fill_image_with_color(data->minimap.wall, data->mlx, data->minimap.tile_size, 0x808080);

	data->minimap.player = mlx_new_image(data->mlx, data->minimap.tile_size, data->minimap.tile_size);
	if (!data->minimap.player)
		ft_kill(data, "Error loading player texture");
	fill_image_with_color(data->minimap.player, data->mlx, data->minimap.tile_size, 0x008000);
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

void	open_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_kill(data, ERR_MLX);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
		ft_kill(data, ERR_MLX_WIN);
	calculate_tile_size(data);
	load_textures(data);
	/* mlx_hook(data->win, KeyPress, KeyPressMask, keypress_handler, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, x_press, data); */
	mlx_loop(data->mlx);
}

void init_minimap(t_data *data)
{
	open_window(data);
}
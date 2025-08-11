/* #include "cub3D.h"

void	fill_image_with_color(void *img, int tile_size, int color)
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
	fill_image_with_color(data->minimap.floor, data->minimap.tile_size, 0x000000);

	data->minimap.wall = mlx_new_image(data->mlx, data->minimap.tile_size, data->minimap.tile_size);
	if (!data->minimap.wall)
		ft_kill(data, "Error loading wall texture");
	fill_image_with_color(data->minimap.wall, data->minimap.tile_size, 0x808080);

	data->minimap.player = mlx_new_image(data->mlx, data->minimap.tile_size, data->minimap.tile_size);
	if (!data->minimap.player)
		ft_kill(data, "Error loading player texture");
	fill_image_with_color(data->minimap.player, data->minimap.tile_size, 0x008000);
}

void	render_minimap(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->map.height && data->map.grid[y])
	{
		x = -1;
		while (++x < data->map.width && data->map.grid[y][x])
			render_image(data, data->map.grid[y][x], x, y);
	}
}


void	render_image(t_data *data, char c, int x, int y)
{
	if (c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		mlx_put_image_to_window(data->mlx, data->win,
			data->minimap.floor, x * data->minimap.tile_size, y * data->minimap.tile_size);
	else if (c == '1')
		mlx_put_image_to_window(data->mlx, data->win,
			data->minimap.wall, x * data->minimap.tile_size, y * data->minimap.tile_size);
	if ((int)data->player.x == x && (int)data->player.y == y) 
		mlx_put_image_to_window(data->mlx, data->win,
			data->minimap.player, data->player.x * data->minimap.tile_size,
			data->player.y * data->minimap.tile_size);
}

void init_minimap(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_kill(data, ERR_MLX);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
		ft_kill(data, ERR_MLX_WIN);
	calculate_tile_size(data);
	load_textures(data);
	render_minimap(data);
	mlx_hook(data->win, KeyPress, KeyPressMask, keypress_handler, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, x_press, data);
	mlx_loop(data->mlx);
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:28:44 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/16 01:28:44 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	minimap_tile_screen(t_minimap *minimap, int px, int py)
{
	double	dx;
	double	dy;

	dx = px - minimap->radius;
	dy = py - minimap->radius;
	minimap->screen_x = minimap->center_x + (((dx + 0.5) * minimap->cos_a
				- (dy + 0.5) * minimap->sin_a) * minimap->tile_size);
	minimap->screen_y = minimap->center_y + (((dx + 0.5) * minimap->sin_a
				+ (dy + 0.5) * minimap->cos_a) * minimap->tile_size);
	minimap->dist_sq = (minimap->screen_x - minimap->center_x)
		* (minimap->screen_x - minimap->center_x)
		+ (minimap->screen_y - minimap->center_y)
		* (minimap->screen_y - minimap->center_y);
	return (minimap->dist_sq <= minimap->radius_px * minimap->radius_px);
}

void	my_mlx_pixel_ignore(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	paint_in_ignore(t_img *img, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			my_mlx_pixel_ignore(img, x, y, color);
	}
}

void	init_minimap(t_data *data)
{
	data->minimap.tile_size = 6;
	data->minimap.radius = 14;
	data->minimap.floor_color = 0x222222;
	data->minimap.wall_color = 0xFFFFFF;
	data->minimap.player_color = 0x00FF00;
	data->minimap.door_color = 0xFF0000;
	data->minimap.size = data->minimap.tile_size
		* (data->minimap.radius * 2 + 1);
	init_img(&data->minimap.minimap_map, data->mlx, data->map.width
		* data->minimap.tile_size, data->map.height * data->minimap.tile_size);
	paint_in_ignore(&data->minimap.minimap_map, IGNORE);
	//init_img(&data->minimap.minimap_buffer, data->mlx, data->minimap.size,
		//data->minimap.size);
}

void	calc_minimap_transform(t_data *data, t_minimap *m)
{
	m->center_x = m->size / 2;
	m->center_y = m->size / 2;
	m->angle = atan2(data->player.dir.y, data->player.dir.x);
	m->cos_a = cos(m->angle + PI / 2);
	m->sin_a = sin(m->angle - PI / 2);
	m->start_tile_x = data->player.x - m->radius;
	m->start_tile_y = data->player.y - m->radius;
	m->radius_px = m->radius * m->tile_size;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	if (color == IGNORE)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_img *img, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			my_mlx_pixel_put(img, x, y, color);
	}
}

//test
void init_img(t_img *img, void *mlx, int width, int height)
{
    img->img = mlx_new_image(mlx, width, height);
    if (!img->img)
        return;
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
    img->width = width;
    img->height = height;
}

int get_tile_color(t_data *data, int x, int y)
{
    char cell;
    int color = 0;

    if (x < 0 || y < 0 || x >= data->map.width || y >= data->map.height)
        return IGNORE;
    cell = data->map.grid[y][x];
    if (cell == '1')
        color = data->minimap.wall_color;
    else if (cell == '0' || ft_strrchr("NSEW", cell))
        color = data->minimap.floor_color;
    else if (ft_strrchr("dDn", cell))
	{
		t_door *door = get_door_at_tile(&data->map, x, y);
		if (is_door_active(data, door))
			color = data->minimap.door_color;
		else
			color = data->minimap.wall_color;
	}
	if (color == IGNORE || color == 0)
		return IGNORE;
	return color;
}

void render_full_minimap_map(t_data *data)
{
    t_minimap *m = &data->minimap;

    //clear_image(&m->minimap_map, IGNORE);

    for (int y = 0; y < data->map.height; y++)
        for (int x = 0; x < data->map.width; x++)
            for (int py = 0; py < m->tile_size; py++)
                for (int px = 0; px < m->tile_size; px++)
                    my_mlx_pixel_put(&m->minimap_map, x*m->tile_size + px, y*m->tile_size + py,
                        get_tile_color(data, x, y));
}

void render_full_door_map(t_data *data)
{
    t_minimap *m = &data->minimap;

    //clear_image(&m->minimap_map, 0x000000);

    for (int y = 0; y < data->map.height; y++)
        for (int x = 0; x < data->map.width; x++)
		{
			if (!ft_strrchr("dDn", data->map.grid[y][x]))
				continue;
            for (int py = 0; py < m->tile_size; py++)
                for (int px = 0; px < m->tile_size; px++)
                    my_mlx_pixel_put(&m->minimap_map, x*m->tile_size + px, y*m->tile_size + py,
                        get_tile_color(data, x, y));
		}
}

void render_minimap(t_data *data)
{
    t_minimap *m = &data->minimap;
    int radius_px = m->radius * m->tile_size;
    double center = m->size / 2;
    double angle = atan2(data->player.dir.y, data->player.dir.x);
    double cos_a = cos(angle + PI / 2);
    double sin_a = sin(angle + PI / 2);

    for (int py = -radius_px; py <= radius_px; py++)
    {
        for (int px = -radius_px; px <= radius_px; px++)
        {
            if (px*px + py*py > radius_px*radius_px)
                continue;

            int dx = (int)(px * cos_a - py * sin_a);
            int dy = (int)(px * sin_a + py * cos_a);

            int map_x = (int)(data->player.x * m->tile_size) + dx;
            int map_y = (int)(data->player.y * m->tile_size) + dy;

            if (map_x >= 0 && map_x < m->minimap_map.width &&
                map_y >= 0 && map_y < m->minimap_map.height)
            {
                int color = get_pixel(&m->minimap_map, map_x, map_y);
                my_mlx_pixel_put(&data->image, px + center, py + center, color);
            }
        }
    }

    // Draw player
    draw_minimap_player(data);

    // Draw border
    draw_minimap_border(data, 0xFFFFFF);

    // Blit to window
    //mlx_put_image_to_window(data->mlx, data->win, m->minimap_buffer.img, m->center_x, m->center_y);
}

void	normalize_map(t_data *data, t_map *map)
{
	int		y;
	int		len;
	char	*new_row;

	for (y = 0; y < map->height; y++)
	{
		len = ft_strlen(map->grid[y]);
		if (len < map->width)
		{
			new_row = malloc(map->width + 1);
			if (!new_row)
				ft_kill(data, ERR_MALLOC);
			ft_memcpy(new_row, map->grid[y], len);
			// pad with spaces (or '1' if you prefer closing walls)
			while (len < map->width)
				new_row[len++] = ' ';
			new_row[len] = '\0';
			free(map->grid[y]);
			map->grid[y] = new_row;
		}
	}
}

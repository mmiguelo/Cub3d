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

void draw_minimap_border(t_img *img, int center_x, int center_y, int radius_px, int color)
{
    for (int angle = 0; angle < 360; angle++)
    {
        int x = center_x + (int)(cos(angle * PI / 180.0) * radius_px);
        int y = center_y + (int)(sin(angle * PI / 180.0) * radius_px);
        my_mlx_pixel_put(img, x, y, color);
    }
}

void render_full_minimap_map(t_data *data)
{
    t_minimap *m = &data->minimap;

    clear_image(&m->minimap_map, 0x000000);
    for (int y = 0; y < data->map.height; y++)
        for (int x = 0; x < data->map.width; x++)
            for (int py = 0; py < m->tile_size; py++)
                for (int px = 0; px < m->tile_size; px++)
                    my_mlx_pixel_put(&m->minimap_map, x*m->tile_size + px, y*m->tile_size + py,
                        get_tile_color(data, x, y));
}

void init_img(t_img *img, void *mlx, int width, int height)
{
    img->img = mlx_new_image(mlx, width, height);
    if (!img->img)
        return;
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
    img->width = width;
    img->height = height;
}

void init_minimap(t_data *data)
{
    t_minimap *m = &data->minimap;

    m->tile_size = 6;
    m->radius = 14;
    m->floor_color = 0x222222;
    m->wall_color = 0xFFFFFF;
    m->player_color = 0x00FF00;
    m->door_color = 0xFF0000;
    m->size = m->tile_size * (m->radius * 2 + 1);
    m->center_x = 10;
    m->center_y = 10;
    init_img(&m->minimap_buffer, data->mlx, m->size, m->size);
    init_img(&m->minimap_map, data->mlx, data->map.width * m->tile_size, data->map.height * m->tile_size);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
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

void	draw_minimap_tile(t_img *img, int start_x, int start_y, int color, int size)
{
	int x, y;
	for (y = 0; y < size; y++)
		for (x = 0; x < size; x++)
			my_mlx_pixel_put(img, start_x + x, start_y + y, color);
}

void	draw_minimap_player(t_img *img, int center_x, int center_y, int color, int tile_size)
{
	int radius = tile_size/2;
	if (radius < 2) radius = 2;
	for (int y = -radius; y <= radius; y++)
		for (int x = -radius; x <= radius; x++)
			if (x*x + y*y <= radius*radius)
				my_mlx_pixel_put(img, center_x + x, center_y + y, color);
}

void render_minimap(t_data *data)
{
    t_minimap *m = &data->minimap;
    int radius_px = m->radius * m->tile_size;
    double center = m->size / 2;
    double angle = atan2(data->player.dir.y, data->player.dir.x);
    double cos_a = cos(angle + PI/2);
    double sin_a = sin(angle - PI/2);
    clear_image(&m->minimap_buffer, 0x000000);
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
                my_mlx_pixel_put(&m->minimap_buffer, px + center, py + center, color);
            }
        }
    }
    draw_minimap_player(&m->minimap_buffer, center, center, m->player_color, m->tile_size);
    draw_minimap_border(&m->minimap_buffer, center, center, radius_px, 0xFFFFFF);
    mlx_put_image_to_window(data->mlx, data->win, m->minimap_buffer.img, m->center_x, m->center_y);
}

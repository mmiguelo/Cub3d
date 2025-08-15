#include "cub3D_bonus.h"

void	init_fps(t_data *data)
{
	data->frames.time = 0.0;
	data->frames.old_time = 0.0;
	data->frames.delta_time = 0.0;
	data->frames.fps = 0.0;
}

double get_current_time_in_seconds(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	update_fps(t_data *data)
{
	data->frames.time = get_current_time_in_seconds();
	data->frames.delta_time = data->frames.time - data->frames.old_time;
	if (data->frames.delta_time <= 0.0)
		data->frames.delta_time = 0.0001;
	data->frames.fps = 1.0 / data->frames.delta_time;
	data->frames.old_time = data->frames.time;
}

void render_fps(t_data *data)
{
	char fps_text[16];

	sprintf(fps_text, "FPS: %.0f", data->frames.fps);
	mlx_string_put(data->mlx, data->win, WIN_WIDTH - 80, 10, 0xFFFFFF,
		fps_text);
}

void	draw_fps_box(t_img *image)
{
	int x, y;
	int box_width = 70;
	int box_height = 20;
	int start_x = image->width - box_width - 10; // 10px margin
	int start_y = 10;
	char *dst;

	for (y = start_y; y < start_y + box_height; y++)
	{
		for (x = start_x; x < start_x + box_width; x++)
		{
			dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
			*(unsigned int *)dst = 0xFFFFFF; // white box
		}
	}
}

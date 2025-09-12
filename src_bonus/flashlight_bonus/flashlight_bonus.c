#include "cub3D_bonus.h"

void draw_flashlight_overlay(t_data *data)
{
	int		center_x;
	int		center_y;
	double	radius;
	int		x;
	int		y;

	if (!data->fl_on)
		return ;
	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	radius = 600;
	y = -1;
    while (++y < WIN_HEIGHT)
    {
		x = -1;
        while(++x < WIN_WIDTH)
        {
            double dx = x - center_x;
            double dy = y - center_y;
            double dist = sqrt(dx * dx + dy * dy);
            if (dist < radius)
            {
                int color = get_pixel(&data->image, x, y);
                double factor = (2.5 - (dist / radius) * 1.8) * data->fl.flicker_factor;
				if (factor < 1.0)
					factor = 1.0;
                color = apply_brightness(color, factor);
                put_pixel(&data->image, x, y, color);
            }
        }
    }
}

unsigned int get_pixel(t_img *img, int x, int y)
{
    char    *dst;

    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return (0);
    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    return (*(unsigned int *)dst);
}

void	toggle_flashlight(t_data *data)
{
	data->fl_on = !data->fl_on;
	if (data->fl_on)
	{
		data->fl.flicker_frames = 20 + rand() % 20;
		data->fl.flicker_factor = 1.0;
	}
	else
	{
		data->fl.flicker_frames = 0;
		data->fl.flicker_factor = 1.0;
	}
}

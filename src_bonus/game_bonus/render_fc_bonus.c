#include "cub3D_bonus.h"

void	render_fc(t_data *data, t_ray *ray)
{
	int	y;
	int	x;

	ray->floor.pos_z = WIN_HEIGHT * 0.5; // (maybe change 0.5 later if we do rotate up)
	ray->floor.dir0.x = data->player.dir.x - data->player.plane.x;
	ray->floor.dir0.y = data->player.dir.y - data->player.plane.y;
	ray->floor.dir1.x = data->player.dir.x + data->player.plane.x;
	ray->floor.dir1.y = data->player.dir.y + data->player.plane.y;

	// TODO floor
	// 1: Calculate distance from camera to the row
	// 2: Calculate step increments in world space
	// 3: Start world position for this row


	// 4: Loop through pixels in row (x-axis)
	y = WIN_HEIGHT / 2 + 1;
	while (y < WIN_HEIGHT)
	{
		// check
		// draw (from the information we have)
		x = 0;
		while (x < WIN_WIDTH)
		{

			x++;
		}
		y++;
	}

	//side note:
	// Distance from player to current row in world space
	// World coordinate of the current pixel
	// Pick texture (normal ceiling or light)
	// Convert world coord -> texture coord
	// Draw pixel
}

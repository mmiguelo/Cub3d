#include "cub3D_bonus.h"

void	render_fc(t_data *data, t_floorcast *floor)
{
	int	y;
	int	x;
	int	tex_color;

	floor->dir0.x = data->player.dir.x - data->player.plane.x;
	floor->dir0.y = data->player.dir.y - data->player.plane.y;
	floor->dir1.x = data->player.dir.x + data->player.plane.x;
	floor->dir1.y = data->player.dir.y + data->player.plane.y;
	floor->pos_z = WIN_HEIGHT * 0.5; // (maybe change 0.5 later if we do rotate up)
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		floor->row_distance = floor->pos_z / (y - WIN_HEIGHT / 2);
		x = 0;
		while (x < WIN_WIDTH)
		{
			floor->cell.x = (int)floor->x;
			floor->cell.y = (int)floor->y;
			floor->tex.x = (floor->x - floor->cell.x) * TILE_SIZE;
			floor->tex.y = (floor->y - floor->cell.y) * TILE_SIZE;
			tex_color = color (&data->ray.draw, &data->textures.floor);
			put_pixel(&data->textures.floor, x, y, tex_color);
			//pattern for sky %
			tex_color = (&data->ray.draw, &data->textures.celing);
			put_pixel(&data->textures.celing,
				x, (WIN_HEIGHT - y - 1), tex_color);
			floor->x += floor->step.x;
			floor->y += floor->step.y;
			x++;
		}
		y++;
	}
}
	//side note:
	// Distance from player to current row in world space
	// World coordinate of the current pixel
	// Pick texture (normal ceiling or light)
	// Convert world coord -> texture coord
	// Draw pixel

/*	Player info: player_x, player_y, dir_x, dir_y, plane_x, plane_y.
	Per row: row_distance, floor_step_x, floor_step_y, floor_x, floor_y.
	Textures: tex_floor, tex_ceiling, each with width, height.
	Screen info: screen_width, screen_height. */

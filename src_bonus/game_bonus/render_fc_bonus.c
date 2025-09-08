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
	//FLOOR (CEILING y < WIN_HEIGHT/2)
	while (y < WIN_HEIGHT)
	{
		floor->row_distance = floor->pos_z / (y - WIN_HEIGHT / 2.0);
		floor->x = data->player.x + floor->row_distance * floor->dir0.x;
		floor->y = data->player.y + floor->row_distance * floor->dir0.y;
		floor->step.x = (floor->dir1.x - floor->dir0.x) /WIN_WIDTH;
		floor->step.y = (floor->dir1.y - floor->dir0.y) /WIN_WIDTH;
		x = 0;
		while (x < WIN_WIDTH)
		{
			double frac_x = fmod(floor->x, 1.0);
			if (frac_x < 0) 
				frac_x += 1.0;
			double frac_y = fmod(floor->y, 1.0);
			if (frac_y < 0)
				 frac_y += 1.0;
			if (y == WIN_HEIGHT/2 + 10 && x == WIN_WIDTH/2) 
			{
    			printf("floor->x=%.3f, floor->y=%.3f, cell.x=%d, cell.y=%d\n", 
           			floor->x, floor->y, floor->cell.x, floor->cell.y);
    			printf("frac_x=%.3f, frac_y=%.3f\n", floor->tex.x, floor->tex.y);
			}
			data->ray.draw.tex_x = (int)(frac_x * data->textures.floor.width);
			data->ray.draw.tex_y = (int)(frac_y * data->textures.floor.height);
			if (y == WIN_HEIGHT/2 + 10 && x == WIN_WIDTH/2) 
			{
    			printf("tex_x=%d, tex_y=%d, tex_width=%d, tex_height=%d\n", 
           			data->ray.draw.tex_x, data->ray.draw.tex_y, 
           			data->textures.floor.width, data->textures.floor.height);
			}
			tex_color = color(&data->ray.draw, &data->textures.floor);
			put_pixel(&data->bg, x, y, tex_color);
			//ceiling
			// data->ray.draw.tex_x = (int)(floor->tex.x * data->textures.celing.width) % data->textures.celing.width;
			// data->ray.draw.tex_y = (int)((1.0 - floor->tex.y) * data->textures.celing.height) % data->textures.celing.height;
			data->ray.draw.tex_x = (int)(frac_x * data->textures.celing.width);
			float ceil_frac_y = 1.0 - frac_y;
			if (ceil_frac_y < 0) 
				ceil_frac_y += 1.0;
			if (ceil_frac_y >= 1.0) 
				ceil_frac_y -= 1.0;
			tex_color = color(&data->ray.draw, &data->textures.celing);
			put_pixel(&data->bg,
				x, (WIN_HEIGHT - y - 1), tex_color);
			floor->x += floor->step.x;
			floor->y += floor->step.y;
			x++;
		}
		y++;
	}
}

/* void	render_fc(t_data *data, t_floorcast *floor)
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
	//FLOOR (CEILING y < WIN_HEIGHT/2)
	while (y < WIN_HEIGHT)
	{
		floor->row_distance = floor->pos_z / (y - WIN_HEIGHT / 2.0);
		floor->x = data->player.x + floor->row_distance * floor->dir0.x;
		floor->y = data->player.y + floor->row_distance * floor->dir0.y;
		floor->step.x = (floor->dir1.x - floor->dir0.x) /WIN_WIDTH;
		floor->step.y = (floor->dir1.y - floor->dir0.y) /WIN_WIDTH;
		x = 0;
		while (x < WIN_WIDTH)
		{
			floor->cell.x = (int)floor->x;
			floor->cell.y = (int)floor->y;
			floor->tex.x = fmod(floor->x, 1.0);
			if (floor->tex.x < 0)
    			floor->tex.x += 1.0;
			floor->tex.y = fmod(floor->y, 1.0);
			if (floor->tex.y < 0)
    			floor->tex.y += 1.0;
			if (y == WIN_HEIGHT/2 + 10 && x == WIN_WIDTH/2) 
			{
    			printf("floor->x=%.3f, floor->y=%.3f, cell.x=%d, cell.y=%d\n", 
           			floor->x, floor->y, floor->cell.x, floor->cell.y);
    			printf("frac_x=%.3f, frac_y=%.3f\n", floor->tex.x, floor->tex.y);
			}
			data->ray.draw.tex_x = (int)(floor->tex.x * data->textures.floor.width);
			data->ray.draw.tex_y = (int)(floor->tex.y * data->textures.floor.height);
			if (data->ray.draw.tex_x < 0) 
				data->ray.draw.tex_x += data->textures.floor.width;
			if (data->ray.draw.tex_y < 0) 
				data->ray.draw.tex_y += data->textures.floor.height;
			if (y == WIN_HEIGHT/2 + 10 && x == WIN_WIDTH/2) 
			{
    			printf("tex_x=%d, tex_y=%d, tex_width=%d, tex_height=%d\n", 
           			data->ray.draw.tex_x, data->ray.draw.tex_y, 
           			data->textures.floor.width, data->textures.floor.height);
			}
			tex_color = color(&data->ray.draw, &data->textures.floor);
			put_pixel(&data->bg, x, y, tex_color);
			//ceiling
			// data->ray.draw.tex_x = (int)(floor->tex.x * data->textures.celing.width) % data->textures.celing.width;
			// data->ray.draw.tex_y = (int)((1.0 - floor->tex.y) * data->textures.celing.height) % data->textures.celing.height;
			data->ray.draw.tex_x = (int)(floor->tex.x * data->textures.celing.width);
			data->ray.draw.tex_y = (int)((1.0 - floor->tex.y) * data->textures.celing.height);
			if (data->ray.draw.tex_y >= data->textures.celing.height)
    			data->ray.draw.tex_y = data->textures.celing.height - 1;
			tex_color = color(&data->ray.draw, &data->textures.celing);
			put_pixel(&data->bg,
				x, (WIN_HEIGHT - y - 1), tex_color);
			floor->x += floor->step.x;
			floor->y += floor->step.y;
			x++;
		}
		y++;
	}
} */

/* void	render_fc(t_data *data, t_floorcast *floor)
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
	//FLOOR (CEILING y < WIN_HEIGHT/2)
	while (y < WIN_HEIGHT)
	{
		floor->row_distance = floor->pos_z / (y - WIN_HEIGHT / 2.0);
		floor->x = data->player.x + floor->row_distance * floor->dir0.x;
		floor->y = data->player.y + floor->row_distance * floor->dir0.y;
		floor->step.x = (floor->dir1.x - floor->dir0.x) /WIN_WIDTH;
		floor->step.y = (floor->dir1.y - floor->dir0.y) /WIN_WIDTH;
		x = 0;
		while (x < WIN_WIDTH)
		{
			floor->cell.x = (int)floor->x;
			floor->cell.y = (int)floor->y;
			floor->tex.x = (floor->x - floor->cell.x);
			floor->tex.y = (floor->y - floor->cell.y);
			if (y == WIN_HEIGHT/2 + 10 && x == WIN_WIDTH/2) 
			{
    			printf("floor->x=%.3f, floor->y=%.3f, cell.x=%d, cell.y=%d\n", 
           			floor->x, floor->y, floor->cell.x, floor->cell.y);
    			printf("frac_x=%.3f, frac_y=%.3f\n", floor->tex.x, floor->tex.y);
			}
			data->ray.draw.tex_x = (int)(floor->tex.x * data->textures.floor.width) % data->textures.floor.width;
			data->ray.draw.tex_y = (int)(floor->tex.y * data->textures.floor.height) % data->textures.floor.height;
			if (data->ray.draw.tex_x < 0) 
				data->ray.draw.tex_x += data->textures.floor.width;
			if (data->ray.draw.tex_y < 0) 
				data->ray.draw.tex_y += data->textures.floor.height;
			if (y == WIN_HEIGHT/2 + 10 && x == WIN_WIDTH/2) 
			{
    			printf("tex_x=%d, tex_y=%d, tex_width=%d, tex_height=%d\n", 
           			data->ray.draw.tex_x, data->ray.draw.tex_y, 
           			data->textures.floor.width, data->textures.floor.height);
			}
			tex_color = color(&data->ray.draw, &data->textures.floor);
			put_pixel(&data->bg, x, y, tex_color);
			//ceiling
			data->ray.draw.tex_x = (int)(floor->tex.x * data->textures.celing.width) % data->textures.celing.width; 
			data->ray.draw.tex_y = (int)(floor->tex.y * data->textures.celing.height) % data->textures.celing.height;
			if (data->ray.draw.tex_x < 0) 
				data->ray.draw.tex_x += data->textures.celing.width;
			if (data->ray.draw.tex_y < 0) 
				data->ray.draw.tex_y += data->textures.celing.height;
			tex_color = color(&data->ray.draw, &data->textures.celing);
			put_pixel(&data->bg,
				x, (WIN_HEIGHT - y - 1), tex_color);
			floor->x += floor->step.x;
			floor->y += floor->step.y;
			x++;
		}
		y++;
	}
} */

//data->ray.draw.tex_x = ((int)((floor->x - floor->cell.x) * data->textures.floor.width) + data->textures.floor.width) % data->textures.floor.width;
			//data->ray.draw.tex_y = ((int)((floor->y - floor->cell.y) * data->textures.floor.height) + data->textures.floor.height) % data->textures.floor.height;
			/* if (data->ray.draw.tex_x < 0 || data->ray.draw.tex_x >= data->textures.floor.width ||
		    data->ray.draw.tex_y < 0 || data->ray.draw.tex_y >= data->textures.floor.height)
			{
			    printf("OOB! tex_x=%d tex_y=%d\n", data->ray.draw.tex_x, data->ray.draw.tex_y);
			} */
//pattern for sky %
			// data->ray.draw.tex_x = (int)((floor->x - floor->cell.x) * data->textures.celing.width);
			// data->ray.draw.tex_y = (int)((floor->y - floor->cell.y) * data->textures.celing.height);

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

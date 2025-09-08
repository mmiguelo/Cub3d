#include "cub3D_bonus.h"
#include <math.h>

#define TEXTURE_SCALE 1.0

void	render_fc(t_data *data, t_fccast *fc)
{
	int	y;
	int	x;
	int	tex_color;

	fc->dir0.x = data->player.dir.x - data->player.plane.x;
	fc->dir0.y = data->player.dir.y - data->player.plane.y;
	fc->dir1.x = data->player.dir.x + data->player.plane.x;
	fc->dir1.y = data->player.dir.y + data->player.plane.y;
	fc->pos_z = WIN_HEIGHT * 0.5; // (maybe change 0.5 later if we do rotate up)
	y = WIN_HEIGHT / 2;
	//FLOOR (CEILING y < WIN_HEIGHT/2)
	while (y < WIN_HEIGHT)
	{
		fc->row_distance = fc->pos_z / (y - WIN_HEIGHT / 2.0);
		fc->x = data->player.x + fc->row_distance * fc->dir0.x;
		fc->y = data->player.y + fc->row_distance * fc->dir0.y;
		fc->step.x = (fc->dir1.x - fc->dir0.x) /WIN_WIDTH;
		fc->step.y = (fc->dir1.y - fc->dir0.y) /WIN_WIDTH;
		x = 0;
		while (x < WIN_WIDTH)
		{
			fc->cell.x = (int)floor(fc->x);
            fc->cell.y = (int)floor(fc->y);
			fc->tex.x = fc->x - fc->cell.x;
            fc->tex.y = fc->y - fc->cell.y;
			if (fc->tex.x < 0.0)
                fc->tex.x += 1.0;
            if (fc->tex.y < 0.0)
                fc->tex.y += 1.0;
			 if (y == WIN_HEIGHT/2 + 10 && x == WIN_WIDTH/2)
            {
                printf("fc->x=%.3f, fc->y=%.3f, cell.x=%d, cell.y=%d\n",
                       fc->x, fc->y, fc->cell.x, fc->cell.y);
                printf("frac_x=%.3f, frac_y=%.3f\n", fc->tex.x, fc->tex.y);
                printf("step_x=%d, step_y=%d, row_distance=%.3f\n", 
                       fc->step.x, fc->step.y, fc->row_distance);
            }
			data->ray.draw.tex_x = (int)(fc->tex.x * data->textures.floor.width) % data->textures.floor.width;
            data->ray.draw.tex_y = (int)(fc->tex.y * data->textures.floor.height) % data->textures.floor.height;
			/* data->ray.draw.tex_x = (int)(fc->tex.x * data->textures.floor.width * TEXTURE_SCALE) % data->textures.floor.width;
			data->ray.draw.tex_y = (int)(fc->tex.y * data->textures.floor.height * TEXTURE_SCALE) % data->textures.floor.height; */
			 if (data->ray.draw.tex_x < 0)
                data->ray.draw.tex_x += data->textures.floor.width;
            if (data->ray.draw.tex_y < 0)
                data->ray.draw.tex_y += data->textures.floor.height;
			tex_color = color(&data->ray.draw, &data->textures.floor);
			put_pixel(&data->bg, x, y, tex_color);
			//ceiling
			data->ray.draw.tex_x = (int)(fc->tex.x * data->textures.celing.width) % data->textures.celing.width;
            data->ray.draw.tex_y = (int)(fc->tex.y * data->textures.celing.height) % data->textures.celing.height;
            // Safety bounds checking for ceiling
            if (data->ray.draw.tex_x < 0)
                data->ray.draw.tex_x += data->textures.celing.width;
            if (data->ray.draw.tex_y < 0)
                data->ray.draw.tex_y += data->textures.celing.height;
			tex_color = color(&data->ray.draw, &data->textures.celing);
			put_pixel(&data->bg,
				x, (WIN_HEIGHT - y - 1), tex_color);
			fc->x += fc->step.x;
			fc->y += fc->step.y;
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

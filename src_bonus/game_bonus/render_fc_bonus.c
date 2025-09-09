#include "cub3D_bonus.h"
#include <math.h>

#define TEXTURE_SCALE 1.0

// void render_fc(t_data *data, t_fccast *fc)
// {
//     int y, x, tex_color;
//     int horizon; // Dynamic horizon line
    
//     fc->dir0.x = data->player.dir.x - data->player.plane.x;
//     fc->dir0.y = data->player.dir.y - data->player.plane.y;
//     fc->dir1.x = data->player.dir.x + data->player.plane.x;
//     fc->dir1.y = data->player.dir.y + data->player.plane.y;
    
//     // Calculate horizon based on player height (0.0 = looking down, 1.0 = looking up)
//     horizon = WIN_HEIGHT / 2 + (int)((data->player.height - 0.5) * WIN_HEIGHT);
//     fc->pos_z = WIN_HEIGHT * 0.5; // Keep this constant for proper perspective
    
//     // Render floor (below horizon)
//     y = horizon;
//     while (y < WIN_HEIGHT)
//     {
//         if (y == horizon) { y++; continue; } // Skip horizon line to avoid division by zero
        
//         fc->row_distance = fc->pos_z / (y - horizon);
//         fc->x = data->player.x + fc->row_distance * fc->dir0.x;
//         fc->y = data->player.y + fc->row_distance * fc->dir0.y;
        
//         fc->step.x = fc->row_distance * (fc->dir1.x - fc->dir0.x) / WIN_WIDTH;
//         fc->step.y = fc->row_distance * (fc->dir1.y - fc->dir0.y) / WIN_WIDTH;
        
//         x = 0;
//         while (x < WIN_WIDTH)
//         {
//             fc->cell.x = (int)floor(fc->x);
// 			fc->cell.y = (int)floor(fc->y);
// 			fc->tex.x = fc->x - fc->cell.x;
// 			fc->tex.y = fc->y - fc->cell.y;
			
// 			if (fc->tex.x < 0.0)
// 				fc->tex.x += 1.0;
// 			if (fc->tex.y < 0.0)
// 				fc->tex.y += 1.0;
			
//            /*  if (y == WIN_HEIGHT/2 + 10 && x == WIN_WIDTH/2)
//             {
//                 printf("fc->x=%.3f, fc->y=%.3f, cell.x=%d, cell.y=%d\n",
//                        fc->x, fc->y, fc->cell.x, fc->cell.y);
//                 printf("frac_x=%.3f, frac_y=%.3f\n", fc->tex.x, fc->tex.y);
//                 printf("step_x=%.6f, step_y=%.6f, row_distance=%.3f\n",
//                        fc->step.x, fc->step.y, fc->row_distance);
//             } */
            
//             // Floor texture
// 			data->ray.draw.tex_x = (int)(fc->tex.x * data->textures.floor.width) % data->textures.floor.width;
// 			data->ray.draw.tex_y = (int)(fc->tex.y * data->textures.floor.height) % data->textures.floor.height;
			
// 			if (data->ray.draw.tex_x < 0)
// 				data->ray.draw.tex_x += data->textures.floor.width;
// 			if (data->ray.draw.tex_y < 0)
// 				data->ray.draw.tex_y += data->textures.floor.height;

// 			tex_color = color(&data->ray.draw, &data->textures.floor);
// 			put_pixel(&data->bg, x, y, tex_color);
//             fc->x += fc->step.x;
//             fc->y += fc->step.y;
//             x++;
//         }
//         y++;
//     }
    
//     // Render ceiling (above horizon)
//     y = horizon - 1;
//     while (y >= 0)
//     {
//         fc->row_distance = fc->pos_z / (horizon - y);
//         fc->x = data->player.x + fc->row_distance * fc->dir0.x;
//         fc->y = data->player.y + fc->row_distance * fc->dir0.y;
        
//         fc->step.x = fc->row_distance * (fc->dir1.x - fc->dir0.x) / WIN_WIDTH;
//         fc->step.y = fc->row_distance * (fc->dir1.y - fc->dir0.y) / WIN_WIDTH;
        
//         x = 0;
//         while (x < WIN_WIDTH)
//         {
// 			fc->cell.x = (int)floor(fc->x);
// 			fc->cell.y = (int)floor(fc->y);
// 			fc->tex.x = fc->x - fc->cell.x;
// 			fc->tex.y = fc->y - fc->cell.y;
			
// 			if (fc->tex.x < 0.0)
// 				fc->tex.x += 1.0;
// 			if (fc->tex.y < 0.0)
// 				fc->tex.y += 1.0;
			
//            /*  if (y == WIN_HEIGHT/2 + 10 && x == WIN_WIDTH/2)
//             {
//                 printf("fc->x=%.3f, fc->y=%.3f, cell.x=%d, cell.y=%d\n",
//                        fc->x, fc->y, fc->cell.x, fc->cell.y);
//                 printf("frac_x=%.3f, frac_y=%.3f\n", fc->tex.x, fc->tex.y);
//                 printf("step_x=%.6f, step_y=%.6f, row_distance=%.3f\n",
//                        fc->step.x, fc->step.y, fc->row_distance);
//             } */
// 			data->ray.draw.tex_x = (int)(fc->tex.x * data->textures.celing.width) % data->textures.celing.width;
// 			data->ray.draw.tex_y = (int)(fc->tex.y * data->textures.celing.height) % data->textures.celing.height;
			
// 			if (data->ray.draw.tex_x < 0)
// 			    data->ray.draw.tex_x += data->textures.celing.width;
// 			if (data->ray.draw.tex_y < 0)
// 			    data->ray.draw.tex_y += data->textures.celing.height;
// 			tex_color = color(&data->ray.draw, &data->textures.celing);
// 			put_pixel(&data->bg, x, y, tex_color);
//             fc->x += fc->step.x;
//             fc->y += fc->step.y;
//             x++;
//         }
//         y--;
//     }
// }

void	init_fc_directions(t_data *data, t_fccast *fc)
{
	fc->dir0.x = data->player.dir.x - data->player.plane.x;
	fc->dir0.y = data->player.dir.y - data->player.plane.y;
	fc->dir1.x = data->player.dir.x + data->player.plane.x;
	fc->dir1.y = data->player.dir.y + data->player.plane.y;
	fc->pos_z = WIN_HEIGHT * 0.5;
	//fc->horizon = P_HEIGHT;
}

void	calculate_text_coord(t_fccast *fc)
{
	fc->cell.x = (int)floor(fc->x);
	fc->cell.y = (int)floor(fc->y);
	fc->tex.x = fc->x - fc->cell.x;
	fc->tex.y = fc->y - fc->cell.y;
	if (fc->tex.x < 0.0)
		fc->tex.x += 1.0;
	if (fc->tex.y < 0.0)
		fc->tex.y += 1.0;
}

void	render_floor_pixel(t_data *data, t_fccast *fc, int x, int y)
{
	int	tex_color;

	data->ray.draw.tex_x = (int)(fc->tex.x * data->textures.floor.width) % data->textures.floor.width;
	data->ray.draw.tex_y = (int)(fc->tex.y * data->textures.floor.height) % data->textures.floor.height;
	if (data->ray.draw.tex_x < 0)
		data->ray.draw.tex_x += data->textures.floor.width;
	if (data->ray.draw.tex_y < 0)
		data->ray.draw.tex_y += data->textures.floor.height;
	tex_color = color(&data->ray.draw, &data->textures.floor);
	put_pixel(&data->bg, x, y, tex_color);
}

void	render_ceiling_pixel(t_data *data, t_fccast *fc, int x, int y)
{
		int	tex_color;

	data->ray.draw.tex_x = (int)(fc->tex.x * data->textures.celing.width) % data->textures.celing.width;
	data->ray.draw.tex_y = (int)(fc->tex.y * data->textures.celing.height) % data->textures.celing.height;
	if (data->ray.draw.tex_x < 0)
		data->ray.draw.tex_x += data->textures.celing.width;
	if (data->ray.draw.tex_y < 0)
		data->ray.draw.tex_y += data->textures.celing.height;
	tex_color = color(&data->ray.draw, &data->textures.celing);
	put_pixel(&data->bg, x, (WIN_HEIGHT - y - 1), tex_color);
}

void	render_fc_row(t_data *data, t_fccast *fc, int y)
{
	int	x;

	fc->row_distance = fc->pos_z / (y - WIN_HEIGHT / 2.0);
	fc->x = data->player.x + fc->row_distance * fc->dir0.x;
	fc->y = data->player.y + fc->row_distance * fc->dir0.y;
	fc->step.x = fc->row_distance * (fc->dir1.x - fc->dir0.x) / WIN_WIDTH;
	fc->step.y = fc->row_distance * (fc->dir1.y - fc->dir0.y) / WIN_WIDTH;
	x = 0;
	while (x < WIN_WIDTH)
	{
		calculate_text_coord(fc);
		render_floor_pixel(data, fc, x, y);
		render_ceiling_pixel(data, fc, x, y);
		fc->x += fc->step.x;
		fc->y += fc->step.y;
		x++;
	}
}

void render_fc(t_data *data, t_fccast *fc)
{
	int	y;

	init_fc_directions(data, fc);
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		render_fc_row(data, fc, y);
		y++;
	}
}

// void render_fc(t_data *data, t_fccast *fc)
// {
// 	int y;
// 	int x;
// 	int tex_color;

// 	fc->dir0.x = data->player.dir.x - data->player.plane.x;
// 	fc->dir0.y = data->player.dir.y - data->player.plane.y;
// 	fc->dir1.x = data->player.dir.x + data->player.plane.x;
// 	fc->dir1.y = data->player.dir.y + data->player.plane.y;
// 	fc->pos_z = WIN_HEIGHT * 0.5;

// 	y = WIN_HEIGHT / 2;
// 	while (y < WIN_HEIGHT)
// 	{
// 		fc->row_distance = fc->pos_z / (y - WIN_HEIGHT / 2.0);
// 		fc->x = data->player.x + fc->row_distance * fc->dir0.x;
// 		fc->y = data->player.y + fc->row_distance * fc->dir0.y;
		
// 		// Calculate step with row_distance multiplier
// 		fc->step.x = fc->row_distance * (fc->dir1.x - fc->dir0.x) / WIN_WIDTH;
// 		fc->step.y = fc->row_distance * (fc->dir1.y - fc->dir0.y) / WIN_WIDTH;
		
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			fc->cell.x = (int)floor(fc->x);
// 			fc->cell.y = (int)floor(fc->y);
// 			fc->tex.x = fc->x - fc->cell.x;
// 			fc->tex.y = fc->y - fc->cell.y;
			
// 			if (fc->tex.x < 0.0)
// 				fc->tex.x += 1.0;
// 			if (fc->tex.y < 0.0)
// 				fc->tex.y += 1.0;
			
//            /*  if (y == WIN_HEIGHT/2 + 10 && x == WIN_WIDTH/2)
//             {
//                 printf("fc->x=%.3f, fc->y=%.3f, cell.x=%d, cell.y=%d\n",
//                        fc->x, fc->y, fc->cell.x, fc->cell.y);
//                 printf("frac_x=%.3f, frac_y=%.3f\n", fc->tex.x, fc->tex.y);
//                 printf("step_x=%.6f, step_y=%.6f, row_distance=%.3f\n",
//                        fc->step.x, fc->step.y, fc->row_distance);
//             } */
            
//             // Floor texture
// 			data->ray.draw.tex_x = (int)(fc->tex.x * data->textures.floor.width) % data->textures.floor.width;
// 			data->ray.draw.tex_y = (int)(fc->tex.y * data->textures.floor.height) % data->textures.floor.height;
			
// 			if (data->ray.draw.tex_x < 0)
// 				data->ray.draw.tex_x += data->textures.floor.width;
// 			if (data->ray.draw.tex_y < 0)
// 				data->ray.draw.tex_y += data->textures.floor.height;

// 			tex_color = color(&data->ray.draw, &data->textures.floor);
// 			put_pixel(&data->bg, x, y, tex_color);
			
// 			// Ceiling texture
// 			data->ray.draw.tex_x = (int)(fc->tex.x * data->textures.celing.width) % data->textures.celing.width;
// 			data->ray.draw.tex_y = (int)(fc->tex.y * data->textures.celing.height) % data->textures.celing.height;
			
// 			if (data->ray.draw.tex_x < 0)
// 			    data->ray.draw.tex_x += data->textures.celing.width;
// 			if (data->ray.draw.tex_y < 0)
// 			    data->ray.draw.tex_y += data->textures.celing.height;
			
// 			tex_color = color(&data->ray.draw, &data->textures.celing);
// 			put_pixel(&data->bg, x, (WIN_HEIGHT - y - 1), tex_color);
			
// 			// Move to next pixel using fc->step
// 			fc->x += fc->step.x;
// 			fc->y += fc->step.y;
// 			x++;
// 		}
// 	y++;
// 	}
// }

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

#include "cub3D_bonus.h"

void	lerp_day_cycle_fc(t_data *data, double day_cycle)
{
	day_cycle = fmod(day_cycle, 1.0);
	if (day_cycle < 0.25)
	{
		if (data->bmoon)
			change_day(&data->bmoon, &data->bsunrise);
	}
	else if (day_cycle < 0.5)
	{
		if (data->bsunrise)
			change_day(&data->bsunrise, &data->bsun);
	}
	else if (day_cycle < 0.75)
	{
		if (data->bsun)
			change_day(&data->bsun, &data->bsunset);
	}
	else
	{
		if (data->bsunset)
			change_day(&data->bsunset, &data->bmoon);
	}
}

void	init_fc_directions(t_data *data, t_fccast *fc)
{
	fc->dir0.x = data->player.dir.x - data->player.plane.x;
	fc->dir0.y = data->player.dir.y - data->player.plane.y;
	fc->dir1.x = data->player.dir.x + data->player.plane.x;
	fc->dir1.y = data->player.dir.y + data->player.plane.y;
	fc->pos_z = WIN_HEIGHT * 0.5;
	fc->horizon = fc->pos_z + (int)((data->player.height - 0.5) * WIN_HEIGHT);
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

void	render_fc_pixel(t_data *data, t_fccast *fc, t_img *texture)
{
	int		tex_color;
	double	brightness;

	data->ray.draw.tex_x = (int)(fc->tex.x * texture->width) % texture->width;
	data->ray.draw.tex_y = (int)(fc->tex.y * texture->height) % texture->height;
	if (data->ray.draw.tex_x < 0)
		data->ray.draw.tex_x += texture->width;
	if (data->ray.draw.tex_y < 0)
		data->ray.draw.tex_y += texture->height;
	brightness = 1.0 / (1.0 + fc->row_distance * DARKNESS);
	if (brightness < 0.2)
		brightness = 0.2;
	tex_color = color(&data->ray.draw, texture);
	tex_color = apply_global_brightness(tex_color, data->global_light * brightness);
	put_pixel(&data->image, fc->temp.x, fc->temp.y, tex_color);
}

void	render_fc_row(t_data *data, t_fccast *fc, t_img *texture, int y)
{
	int	x;

	fc->x = data->player.x + fc->row_distance * fc->dir0.x;
	fc->y = data->player.y + fc->row_distance * fc->dir0.y;
	fc->step.x = fc->row_distance * (fc->dir1.x - fc->dir0.x) / WIN_WIDTH;
	fc->step.y = fc->row_distance * (fc->dir1.y - fc->dir0.y) / WIN_WIDTH;
	x = 0;
	while (x < WIN_WIDTH)
	{
		calculate_text_coord(fc);
		fc->temp.x = x;
		fc->temp.y = y;
		render_fc_pixel(data, fc, texture);
		fc->x += fc->step.x;
		fc->y += fc->step.y;
		x++;
	}
}

void render_fc(t_data *data, t_fccast *fc)
{
	int	y;

	init_fc_directions(data, fc);
	y = fc->horizon;
	while (y < WIN_HEIGHT)
	{
		fc->row_distance = fc->pos_z / (y - fc->horizon);
		render_fc_row(data, fc, &data->textures.floor, y);
		y++;
	}
	y = fc->horizon - 1;
	while (y >= 0)
	{
		fc->row_distance = fc->pos_z / (fc->horizon - y);
		render_fc_row(data, fc, &data->textures.ceiling, y);
		y--;
	}
	lerp_day_cycle_fc(data, data->time_of_day);
}

// void render_fc(t_data *data, t_fccast *fc)
// {
//     int y, x, tex_color;
//     int horizon; // Dynamic horizon line
    
//     fc->dir0.x = data->player.dir.x - data->player.plane.x;
//     fc->dir0.y = data->player.dir.y - data->player.plane.y;
//     fc->dir1.x = data->player.dir.x + data->player.plane.x;
//     fc->dir1.y = data->player.dir.y + data->player.plane.y;
// 	fc->pos_z = WIN_HEIGHT * 0.5; // Keep this constant for proper perspective
//     // Calculate horizon based on player height (0.0 = looking down, 1.0 = looking up)
//     horizon = fc->pos_z + (int)((data->player.height - 0.5) * WIN_HEIGHT);
    
//     // Render floor (below horizon)
//     y = horizon;
//     while (y < WIN_HEIGHT)
//     {
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
// 			data->ray.draw.tex_x = (int)(fc->tex.x * data->textures.ceiling.width) % data->textures.ceiling.width;
// 			data->ray.draw.tex_y = (int)(fc->tex.y * data->textures.ceiling.height) % data->textures.ceiling.height;
			
// 			if (data->ray.draw.tex_x < 0)
// 			    data->ray.draw.tex_x += data->textures.ceiling.width;
// 			if (data->ray.draw.tex_y < 0)
// 			    data->ray.draw.tex_y += data->textures.ceiling.height;
// 			tex_color = color(&data->ray.draw, &data->textures.ceiling);
// 			put_pixel(&data->bg, x, y, tex_color);
//             fc->x += fc->step.x;
//             fc->y += fc->step.y;
//             x++;
//         }
//         y--;
//     }
// }

//pattern for sky %
			// data->ray.draw.tex_x = (int)((floor->x - floor->cell.x) * data->textures.ceiling.width);
			// data->ray.draw.tex_y = (int)((floor->y - floor->cell.y) * data->textures.ceiling.height);

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

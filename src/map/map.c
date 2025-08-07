#include <cub3D.h>

/* void	render_frame(t_data *data)
{
	int		x;
	double	camera_x, raydir_x, raydir_y;
	int		map_x, map_y;
	double	side_dist_x, side_dist_y;
	double	delta_dist_x, delta_dist_y;
	double	perp_wall_dist;
	int		step_x, step_y;
	int		hit, side;
	int		line_height, draw_start, draw_end;
	double	wall_x, step, tex_pos;
	t_tex	*tex;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2 * x / (double)WIN_WIDTH - 1;
		raydir_x = data->player.dir.x + data->player.plane.x * camera_x;
		raydir_y = data->player.dir.y + data->player.plane.y * camera_x;
		map_x = (int)data->player.x;
		map_y = (int)data->player.y;
		delta_dist_x = fabs(1 / raydir_x);
		delta_dist_y = fabs(1 / raydir_y);
		hit = 0;
		step_x = (raydir_x < 0) ? -1 : 1;
		side_dist_x = (raydir_x < 0)
			? (data->player.x - map_x) * delta_dist_x
			: (map_x + 1.0 - data->player.x) * delta_dist_x;
		step_y = (raydir_y < 0) ? -1 : 1;
		side_dist_y = (raydir_y < 0)
			? (data->player.y - map_y) * delta_dist_y
			: (map_y + 1.0 - data->player.y) * delta_dist_y;

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (data->map.grid[map_y][map_x] != '0')
				hit = 1;
		}

		perp_wall_dist = (side == 0)
			? (side_dist_x - delta_dist_x)
			: (side_dist_y - delta_dist_y);

		line_height = (int)(WIN_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0) draw_start = 0;
		draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

		if (side == 0 && raydir_x > 0)
			tex = &data->textures.west;
		else if (side == 0)
			tex = &data->textures.east;
		else if (raydir_y > 0)
			tex = &data->textures.north;
		else
			tex = &data->textures.south;

		wall_x = (side == 0)
			? data->player.y + perp_wall_dist * raydir_y
			: data->player.x + perp_wall_dist * raydir_x;
		wall_x -= floor(wall_x);
		int tex_x = (int)(wall_x * TILE_SIZE);
		if (side == 0 && raydir_x > 0) tex_x = TILE_SIZE - tex_x - 1;
		if (side == 1 && raydir_y < 0) tex_x = TILE_SIZE - tex_x - 1;
		step = 1.0 * TILE_SIZE / line_height;
		tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;

		for (int y = draw_start; y < draw_end; y++)
		{
			int tex_y = (int)tex_pos & (TILE_SIZE - 1);
			tex_pos += step;
			int color = *(int *)(tex->addr + (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8)));
			if (side == 1) color = (color >> 1) & 8355711;
			*(int *)(data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8))) = color;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	handle_keys(t_data *data, double move_speed, double rot_speed)
{
	if (key_pressed(KEY_W))
	{
		if (data->map.grid[(int)(data->player.x + data->player.dir.x * move_speed)][(int)data->player.y] == '0')
			data->player.x += data->player.dir.x * move_speed;
		if (data->map.grid[(int)data->player.x][(int)(data->player.y + data->player.dir.y * move_speed)] == '0')
			data->player.y += data->player.dir.y * move_speed;
	}
	if (key_pressed(KEY_S))
	{
		if (data->map.grid[(int)(data->player.x - data->player.dir.x * move_speed)][(int)data->player.y] == '0')
			data->player.x -= data->player.dir.x * move_speed;
		if (data->map.grid[(int)data->player.x][(int)(data->player.y - data->player.dir.y * move_speed)] == '0')
			data->player.y -= data->player.dir.y * move_speed;
	}
	if (key_pressed(KEY_A))
	{
		double old_dir_x = data->player.dir.x;
		data->player.dir.x = data->player.dir.x * cos(rot_speed) - data->player.dir.y * sin(rot_speed);
		data->player.dir.y = old_dir_x * sin(rot_speed) + data->player.dir.y * cos(rot_speed);
		double old_plane_x = data->player.plane.x;
		data->player.plane.x = data->player.plane.x * cos(rot_speed) - data->player.plane.y * sin(rot_speed);
		data->player.plane.y = old_plane_x * sin(rot_speed) + data->player.plane.y * cos(rot_speed);
	}
	if (key_pressed(KEY_D))
	{
		double old_dir_x = data->player.dir.x;
		data->player.dir.x = data->player.dir.x * cos(-rot_speed) - data->player.dir.y * sin(-rot_speed);
		data->player.dir.y = old_dir_x * sin(-rot_speed) + data->player.dir.y * cos(-rot_speed);
		double old_plane_x = data->player.plane.x;
		data->player.plane.x = data->player.plane.x * cos(-rot_speed) - data->player.plane.y * sin(-rot_speed);
		data->player.plane.y = old_plane_x * sin(-rot_speed) + data->player.plane.y * cos(-rot_speed);
	}
	if (key_pressed(KEY_ESC))
		close_window(data, "Game Closed");
}

int	game_loop(t_data *data)
{
	data->frames.old_time = data->frames.current_time;
	data->frames.current_time = get_time();
	data->frames.delta_time = (data->frames.current_time - data->frames.old_time) / 1000.0;

	double move_speed = data->frames.delta_time * 5.0;
	double rot_speed = data->frames.delta_time * 3.0;

	handle_keys(data, move_speed, rot_speed);
	render_frame(data);
	return (0);
} */

/* void	init_map(t_data *data)
{
	int		x;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		pitch;
	int		draw_start;
	int		draw_end;
	int		texture_num;
	double	wall_x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2 * x / (double)WIN_WIDTH - 1;
		raydir_x = data->player.dir_x + data->player.plane_x * camera_x;
		raydir_y = data->player.dir_y + data->player.plane_y * camera_x;
		map_x = (int)data->player.x;
		map_y = (int)data->player.y;
		delta_dist_x = fabs(1 / raydir_x);
		delta_dist_y = fabs(1 / raydir_y);
		hit = 0;
		if (raydir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player.x) * delta_dist_x;
		}
		if (raydir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player.y) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (data->map.grid[map_y][map_x] != '0')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);
		line_height = (int)(WIN_HEIGHT / perp_wall_dist);
		pitch = line_height / 2 - WIN_HEIGHT / 2; //change maybe
		draw_start = -line_height / 2 + WIN_HEIGHT / 2 + pitch;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WIN_HEIGHT / 2 + pitch;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		t_tex *tex;
		if (side == 0 && raydir_x > 0)
			tex = &data->textures.west;
		else if (side == 0 && raydir_x < 0)
			tex = &data->textures.east;
		else if (side == 1 && raydir_y > 0)
			tex = &data->textures.north;
		else
			tex = &data->textures.south;
		if (side == 0)
			wall_x = data->player.y + perp_wall_dist * raydir_y;
		else
			wall_x = data->player.x + perp_wall_dist * raydir_x;
		wall_x -= floor(wall_x);
		int tex_x = (int)(wall_x * TILE_SIZE);
		if (side == 0 && raydir_x > 0)
			tex_x = TILE_SIZE - tex_x - 1;
		if (side == 1 && raydir_y < 0)
			tex_x = TILE_SIZE - tex_x - 1;
		double step = 1.0 * TILE_SIZE / line_height;
		double tex_pos = (draw_start - pitch - WIN_HEIGHT / 2 + line_height / 2) * step;
		for (int y = draw_start; y < draw_end; y++)
		{
			int tex_y = (int)tex_pos & (TILE_SIZE - 1);
			tex_pos += step;
			int color = *(int *)(tex->addr + (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8)));
			if (side == 1)
				color = (color >> 1) & 8355711;
			*(int *)(img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8))) = color;
		}
		drawBuffer(buffer[0]);
		for (int y = 0; y < WIN_HEIGHT; y++)
		{
			for (int x = 0; x < WIN_WIDTH; x++)
			{
				buffer[y][x] = 0;
		}
		data->frames.old_time = data->frames.current_time;
		data->frames.current_time = get_time();
		data->frames.delta_time = data->frames.current_time - data->frames.old_time / 1000.0;
		print(1.0 / data->frames.delta_time);
		redraw();
		double move_speed = data->frames.delta_time * 5.0;
		double rot_speed = data->frames.delta_time * 3.0;
		readkeys();
		if (key_pressed(KEY_W))
		{
			if(data->map.grid[(int)(data->player.x + data->player.dir.x * move_speed)][(int)data->player.y] == '0')
				data->player.x += data->player.dir.x * move_speed;
			if(data->map.grid[(int)data->player.x][(int)(data->player.y + data->player.dir.y * move_speed)] == '0')
				data->player.y += data->player.dir.y * move_speed;
		}
		if (key_pressed(KEY_S))
		{
			if(data->map.grid[(int)(data->player.x - data->player.dir.x * move_speed)][(int)data->player.y] == '0')
				data->player.x -= data->player.dir.x * move_speed;
			if(data->map.grid[(int)data->player.x][(int)(data->player.y - data->player.dir.y * move_speed)] == '0')
				data->player.y -= data->player.dir.y * move_speed;
		}
		if (key_pressed(KEY_A))
		{
			double old_dir_x = data->player.dir.x;
			data->player.dir.x = data->player.dir.x * cos(rot_speed) - data->player.dir.y * sin(rot_speed);
			data->player.dir.y = old_dir_x * sin(rot_speed) + data->player.dir.y * cos(rot_speed);
			double old_plane_x = data->player.plane.x;
			data->player.plane.x = data->player.plane.x * cos(rot_speed) - data->player.plane.y * sin(rot_speed);
			data->player.plane.y = old_plane_x * sin(rot_speed) + data->player.plane.y * cos(rot_speed);
		}
		if (key_pressed(KEY_D))
		{
			double old_dir_x = data->player.dir.x;
			data->player.dir.x = data->player.dir.x * cos(-rot_speed) - data->player.dir.y * sin(-rot_speed);
			data->player.dir.y = old_dir_x * sin(-rot_speed) + data->player.dir.y * cos(-rot_speed);
			double old_plane_x = data->player.plane.x;
			data->player.plane.x = data->player.plane.x * cos(-rot_speed) - data->player.plane.y * sin(-rot_speed);
			data->player.plane.y = old_plane_x * sin(-rot_speed) + data->player.plane.y * cos(-rot_speed);
		}
		if (key_pressed(KEY_ESC))
			close_window(data, "Game Closed");
		}
	}
}
 */
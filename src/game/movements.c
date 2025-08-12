#include "cub3D.h"

void	calculate_movements(t_data *data)
{
	if (data->player.move_forward)
	{
		data->player.x += data->player.dir.x * MOVE_SPEED;
		data->player.y += data->player.dir.y * MOVE_SPEED;
	}
	if (data->player.move_backward)
	{
		data->player.x -= data->player.dir.x * MOVE_SPEED;
		data->player.y -= data->player.dir.y * MOVE_SPEED;
	}
	if (data->player.move_left)
	{
		data->player.x += data->player.dir.y * MOVE_SPEED;
		data->player.y -= data->player.dir.x * MOVE_SPEED;
	}
	if (data->player.move_right)
	{
		data->player.x -= data->player.dir.y * MOVE_SPEED;
		data->player.y += data->player.dir.x * MOVE_SPEED;
	}
	if (data->player.turn_left)
		calculate_rotation(data, -ROT_SPEED);
	if (data->player.turn_right)
		calculate_rotation(data, ROT_SPEED);
}

void	calculate_rotation(t_data *data, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(rotation_speed)
		- data->player.dir.y * sin(rotation_speed);
	data->player.dir.y = old_dir_x * sin(rotation_speed)
		+ data->player.dir.y * cos(rotation_speed);
	old_plane_x = data->player.plane.x;
	data->player.plane.x = data->player.plane.x * cos(rotation_speed)
		- data->player.plane.y * sin(rotation_speed);
	data->player.plane.y = old_plane_x * sin(rotation_speed)
		+ data->player.plane.y * cos(rotation_speed);
}

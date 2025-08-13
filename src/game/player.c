#include "cub3D.h"

void	calculate_movements(t_player *player, char **map)
{
	if (data->player.move_forward)
	{
		player->new_x = data->player.x + data->player.dir.x * MOVE_SPEED;
		player->new_y = data->player.y + data->player.dir.y * MOVE_SPEED;
		check_collision(player, map);
	}
	if (data->player.move_backward)
	{
		player->new_x = data->player.x - data->player.dir.x * MOVE_SPEED;
		player->new_y = data->player.y - data->player.dir.y * MOVE_SPEED;
		check_collision(player, map);
	}
	if (data->player.move_left)
	{
		player->new_x = data->player.x + data->player.dir.y * MOVE_SPEED;
		player->new_y = data->player.y - data->player.dir.x * MOVE_SPEED;
		check_collision(player, map);
	}
	if (data->player.move_right)
	{
		player->new_x = data->player.x - data->player.dir.y * MOVE_SPEED;
		player->new_y = data->player.y + data->player.dir.x * MOVE_SPEED;
		check_collision(player, map);
	}
	if (data->player.turn_left)
		calculate_rotation(data, -ROT_SPEED);
	if (data->player.turn_right)
		calculate_rotation(data, ROT_SPEED);
}

void	check_collision(t_player *player, char **map,)
{
	if (map[(int)player->y][(int)(player->new_x + PLAYER_RAD)] != '1'
			&& map[(int)player->y][(int)(player->new_x - PLAYER_RAD)] != '1')
	{
		player->x = player->new_x;
	}
	if (map[(int)(player->new_y + PLAYER_RAD)][(int)player->x] != '1'
			&& map[(int)(player->new_y - PLAYER_RAD)][(int)player->x] != '1')
	{
		player->y = player->new_y;
	}
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

void	get_player_vector(t_data *data)
{
	if (data->map.direction == 'N')
	{
		data->player.dir.x = 0;
		data->player.dir.y = -1;
		data->player.plane.x = PLANE_LEN;
		data->player.plane.y = 0;
	}
	if (data->map.direction == 'S')
	{
		data->player.dir.x = 0;
		data->player.dir.y = 1;
		data->player.plane.x = -PLANE_LEN;
		data->player.plane.y = 0;
	}
	get_player_vector2(data);
}

void	get_player_vector2(t_data *data)
{
	if (data->map.direction == 'W')
	{
		data->player.dir.x = -1;
		data->player.dir.y = 0;
		data->player.plane.x = 0;
		data->player.plane.y = -PLANE_LEN;
	}
	if (data->map.direction == 'E')
	{
		data->player.dir.x = 1;
		data->player.dir.y = 0;
		data->player.plane.x = 0;
		data->player.plane.y = PLANE_LEN;
	}
}

#include "cub3D.h"

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

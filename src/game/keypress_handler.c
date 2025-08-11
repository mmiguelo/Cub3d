#include "cub3D.h"

int	keypress_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		return (close_window(data, GAME_ENDED));
	if (keycode == 119 || keycode == XK_Up)
		move_up(data);
	if (keycode == 115 || keycode == XK_Down)
		move_down(data);
	if (keycode == 100 || keycode == XK_Right)
		move_right(data);
	if (keycode == 97 || keycode == XK_Left)
		move_left(data);
	render_minimap(data);
	return (0);
}

int	x_press(t_data *data)
{
	return (close_window(data, GAME_ENDED));
}

void	move_up(t_data *data)
{
	/* double	new_x = data->player.x + data->player.dir.x * data->move_speed; */
	double	new_y = data->player.y - data->player.dir.y * data->move_speed;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y;
	/* if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x; */
	printf("player position: x-> %f, y->%f\n", data->player.x, data->player.y);
	printf("player dir x = %f\n", data->player.dir.x);
}

void	move_down(t_data *data)
{
	//double	new_x = data->player.x - data->player.dir.x * data->move_speed;
	double	new_y = data->player.y + data->player.dir.y * data->move_speed;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y;
/* 	if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x; */
	printf("player position: x-> %f, y->%f\n", data->player.x, data->player.y);
	printf("player dir x = %f\n", data->player.dir.x);
}

void	move_left(t_data *data)
{
	double	new_x = data->player.x - data->player.plane.x * data->move_speed;
	/* double	new_y = data->player.y - data->player.plane.y * data->move_speed;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y; */
	if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x;
	printf("player position: x-> %f, y->%f\n", data->player.x, data->player.y);
	printf("player dir x = %f\n", data->player.dir.x);
}

void	move_right(t_data *data)
{
	double	new_x = data->player.x + data->player.plane.x * data->move_speed;
	/* double	new_y = data->player.y + data->player.plane.y * data->move_speed;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y; */
	if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x;
	printf("player position: x-> %f, y->%f\n", data->player.x, data->player.y);
	printf("player dir x = %f\n", data->player.dir.x);
}

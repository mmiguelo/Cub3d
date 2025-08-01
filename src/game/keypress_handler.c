#include "cub3D.h"

int	keypress_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		return (close_window(data, GAME_ENDED));
	/* if (keycode == 119 || keycode == XK_Up)	
	if (keycode == 115 || keycode == XK_Down)
	if (keycode == 100 || keycode == XK_Right)
	if (keycode == 97 || keycode == XK_Left) */
	return (0);
}

int	x_press(t_data *data)
{
	return (close_window(data, GAME_ENDED));
}
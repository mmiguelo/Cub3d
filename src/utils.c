#include "cub3D.h"

/* ft_free(t_data *data)
{
	;
} */

const char	*message(t_error_code i)
{
	const char	*message[13];

	message[0] = "Arguments are invalid\n";
	message[1] = "File must be *.cub\n";
	message[2] = "Extension must be .cub\n";
	message[3] = "EXtension must be .xpm\n";
	message[4] = "File is invalid or no permissions\n";
	message[5] = "Map is invalid\n";
	message[6] = "Map sent is a directory\n";
	message[7] = "Malloc failed\n";
	message[8] = "Color is invalid\n";
	message[9] = "Texture is invalid\n";
	message[10] = "MLX failed\n";
	message[11] = "Order is invalid\n";
	message[12] = "Duplication found\n";
	return (message[i]);
}

int	ft_kill(t_data *data, t_error_code code)
{
	(void) data;
	/* if (data)
		 ft_free(data); */
	if (code >= 0 && code <= 13)
		ft_printf_fd(2, RED"Error\n%s\n"RST, message(code));
	else
		ft_printf_fd(2, RED"Unkown Error\n"RST);
	exit(EXIT_FAILURE);
}

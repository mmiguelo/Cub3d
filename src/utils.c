#include "cub3D.h"

ft_free(t_data *data)
{
	;
}

const char	*err_message(t_error_code i)
{
	const char	*message[12];

	message[0] = "Arguments are invalid\n";
	message[1] = "File must be *.cub\n";
	message[2] = "Extension must be .cub\n";
	message[3] = "File is invalid or no permissions\n";
	message[4] = "Map is invalid\n";
	message[5] = "Map sent is a directory\n";
	message[6] = "Malloc failed\n";
	message[7] = "Color is invalid\n";
	message[8] = "Texture is invalid\n";
	message[9] = "MLX failed\n";
	message[10] = "Order is invalid\n";
	message[11] = "Duplication found\n";
	return (message[i]);
}

int	ft_kill(t_data *data, t_error_code code)
{
	if (data)
		 ft_free(data);
	if (code >= 0 && code <= 12)
		ft_printf_fd(2, RED"Error\n%s\n"RST, error_message(code));
	else
		ft_printf_fd(2, RED"Unkown Error\n"RST);
	exit(EXIT_FAILURE);
}

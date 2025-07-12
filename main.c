#include "cub3D.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		ft_kill(NULL, ERR_ARGS);
	parse(av[1]); // check file name, extension, directory, readability
	ft_memset(&data, 0, sizeof(t_data)); // memset to structs inside t_data
	init(&data); // calloc to structs inside t_data
	parse_file_content(&data, av[1]);
	//mlx_functions();
	ft_printf_fd(1, G"\nCongratulations\n\n"RST);
	return (0);
}

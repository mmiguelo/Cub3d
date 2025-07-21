#include "cub3D.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		ft_kill(NULL, ERR_ARGS);
	parse(av[1]); // check file name, extension, directory, readability
	data = init();
	parse_file_content(data, av[1]);
	//mlx_functions();
	ft_kill(data, GAME_ENDED);
	ft_printf_fd(1, G"\nCongratulations\n\n"RST);
	return (0);
}

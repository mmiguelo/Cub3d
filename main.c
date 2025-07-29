#include "cub3D.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		ft_kill(NULL, ERR_ARGS);
	data = init();
	parse(data, av[1], ".cub");
	parse_file_content(data, av[1]);
	//mlx_functions();
	ft_kill(data, GAME_ENDED);
	return (0);
}

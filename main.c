#include "cub3D.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		ft_kill(NULL, ERR_ARGS);
	init(&data);
	parse(&data, av[1], ".cub");
	parse_file_content(&data, av[1]);
	get_player_vector(&data);
	print_map(&data);
	game_loop(&data);
	init_minimap(&data);
	return (0);
}

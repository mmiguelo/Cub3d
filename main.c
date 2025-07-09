#include "cub3D.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		parse(av[1]);
		ft_memset(&data, 0, sizeof(t_data));
		//init(&data); // calloc to structs inside t_data
		//parse_file_content(&data, av[1]);
		//mlx_functions();
		ft_printf_fd(1, G"congratulations\n"RST);
	}
	else if (ac != 2)
		ft_kill(NULL, ERR_ARGS);
	else
		ft_kill(NULL, ERR_FILE);
	return (0);
}

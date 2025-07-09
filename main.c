#include "includes/cub3D.h"

int	main(int ac, char **av)
{
	//t_data	*data;

	if (ac == 2)
	{
		parse(av[1]);
		ft_printf_fd(1, G"congratulations\n"RST);
	}
	else if (ac != 2)
		error_msg(ERR_ARGS);
	else
		error_msg(ERR_FILE);
	return (0);
}

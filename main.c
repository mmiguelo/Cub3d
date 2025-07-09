#include "cub3D.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_textures	*texture;

	if (ac == 2)
	{
		parse(av[1]);
		ft_memset(&data, 0, sizeof(t_data));
		ft_memset(&texture, 0, sizeof(t_textures));
		ft_printf_fd(1, G"congratulations\n"RST);
	}
	else if (ac != 2)
		ft_kill(NULL, ERR_ARGS);
	else
		ft_kill(NULL, ERR_FILE);
	return (0);
}

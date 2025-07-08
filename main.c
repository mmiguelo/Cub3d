#include "cub3D.h"

int main(int ac, char **av)
{
	//t_data	*data;

	if (ac == 2)
	{
		if (access(av[1], F_OK | W_OK) == -1)
		{
			error_msg("File doesnt exist or there is no permitions!");
			exit (1);
		}
		if ((check_directory(av[1]) == 0) && check_extension(av[1]) == 0)
			//data = data_init(av[1]);
			ft_printf_fd(1, "its ok");
	}
	else if (ac != 2)
		return (error_msg("No map input or too many arguments"), 1);
	else
		return (error_msg("Invalid file!"), 1);
	return (0);
}

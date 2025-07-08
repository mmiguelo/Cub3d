#include "../includes/cub3D.h"

void	error_msg(const char *error)
{
	ft_printf_fd(2, RED"Error\n%s\n"RST, error);
	return ;
}

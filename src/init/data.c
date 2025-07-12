#include "cub3D.h"

t_data	*init()
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		ft_kill(NULL, ERR_MALLOC);
	ft_memset(data, 0, sizeof(t_data));
	data->ceiling.r = -1;
	data->ceiling.g = -1;
	data->ceiling.b = -1;
	data->floor.r = -1;
	data->floor.g = -1;
	data->floor.b = -1;
	return (data);
}

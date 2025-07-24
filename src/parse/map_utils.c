#include "cub3D.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (!ft_strchr(WS, line[i]))
			return (0);
		i++;
	}
	return (1);
}

#include "cub3D.h"

bool	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (!ft_strchr(WS, line[i]) && !ft_strchr(VALID_MAP_CHARS, line[i]))
			return (false);
		i++;
	}
	return (true);
}

char *clean_ws(t_data *data, char *line)
{
	char *new_line;
	int	width;

	width = count_width(line);
	new_line = ft_calloc((size_t)(width + 1), sizeof(char));
	if (!new_line)
		ft_kill(data, ERR_MALLOC);
	ft_strlcpy(new_line, line, (size_t)width + 1);
	return (new_line);
}

int	count_width(const char *str)
{
	int	i;

	i = 0;
	while (!(ft_has_white_spaces((char *)(str + i))))
		i++;
	return (i);
}

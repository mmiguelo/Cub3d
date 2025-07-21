#include "cub3D.h"

void	assign_rgb(t_data *data, t_color *color, char *line, int *i)
{
	*i += 2;
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] == '\0')
		ft_kill(data, ERR_COLOR);
	if (color->r != -1 || color->g != -1 || color->b != -1)
		ft_kill(data, ERR_DUPLICATION);
	color->r = ft_atoi(&line[*i]);
	if (color->r < MIN_RGB || color->r > MAX_RGB)
		ft_kill(data, ERR_COLOR);
	while (line[*i] != ',' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	color->g = ft_atoi(&line[*i]);
	if (color->g < MIN_RGB || color->g > MAX_RGB)
		ft_kill(data, ERR_COLOR);
	while (line[*i] != ',' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	color->b = ft_atoi(&line[*i]);
	if (color->b < MIN_RGB || color->b > MAX_RGB)
		ft_kill(data, ERR_COLOR);
}

void	check_duplicated_color(t_data *data, t_color *ceiling, t_color *floor)
{
	if (ceiling->r == floor->r && ceiling->g == floor->g
			&& ceiling->b == floor->b)
		ft_kill(data, ERR_DUPLICATION);
}

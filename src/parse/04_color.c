#include "cub3D.h"

void	check_duplicated_color(t_data *data, t_color *ceiling, t_color *floor)
{
	if (ceiling->r == floor->r && ceiling->g == floor->g
		&& ceiling->b == floor->b)
		ft_kill(data, ERR_DUPLICATION);
}

static int	parse_component(t_data *data, char *line, int *i)
{
	int	value;

	if (!ft_isdigit(line[*i]))
		ft_kill(data, ERR_COLOR);
	value = 0;
	while (ft_isdigit(line[*i]))
	{
		value = value * 10 + (line[*i] - '0');
		(*i)++;
	}
	if (value < MIN_RGB || value > MAX_RGB)
		ft_kill(data, ERR_COLOR_RANGE);
	return (value);
}

static void	parse_commas(t_data *data, char *line, int *i, int index)
{
	if (index == 2)
		return ;
	while (ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] != ',')
		ft_kill(data, ERR_COLOR);
	(*i)++;
	while (ft_isspace(line[*i]))
		(*i)++;
}

void	assign_rgb(t_data *data, t_color *color, char *line)
{
	int	i;
	int	values[3];
	int	index;

	if (color->r != -1 || color->g != -1 || color->b != -1)
		ft_kill(data, ERR_DUPLICATION);
	i = 1;
	while (ft_isspace(line[i]))
		i++;
	index = 0;
	while (index < 3)
	{
		values[index] = parse_component(data, line, &i);
		parse_commas(data, line, &i, index);
		index++;
	}
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '\0')
		ft_kill(data, ERR_COLOR_MORE);
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
}

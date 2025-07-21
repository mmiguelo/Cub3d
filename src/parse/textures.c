#include "cub3D.h"

void	check_textures(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && ft_isspace(line[i + 2]) == 1)
		assign_texture(data, &data->textures.north.path, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2]) == 1)
		assign_texture(data, &data->textures.south.path, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2]) == 1)
		assign_texture(data, &data->textures.west.path, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2]) == 1)
		assign_texture(data, &data->textures.east.path, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ' && ft_isspace(line[i + 2]) == 1)
		assign_rgb(data, &data->floor, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ' && ft_isspace(line[i + 2]) == 1)
		assign_rgb(data, &data->ceiling, line, &i);
}

void	assign_texture(t_data *data, char **path, char *line, int *i)
{
	int len;

	*i += 2;
	while (ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] == '\0')
		ft_kill(data, ERR_TEXTURE);
	if (*path)
		ft_kill(data, ERR_DUPLICATION);
	*path = ft_strdup(&line[*i]);
	if (!path)
		ft_kill(data, ERR_MALLOC);
	len = ft_strlen(*path);
	if (len > 0 && (*path)[len - 1] == '\n')
		(*path)[len - 1] = '\0';
	check_extension_texture(data, *path, ".xpm");
}

void	check_duplicated_textures(t_data *data, t_textures *textures)
{
	char	*paths[4];
	int		i;
	int		j;

	i = 0;
	paths[0] = textures->north.path;
	paths[1] = textures->south.path;
	paths[2] = textures->west.path;
	paths[3] = textures->east.path;
	
	while (i <= 4)
	{
		if (!paths[i])
			continue;
		j = i + 1;
		while (j < 4)
		{
			if (paths[j] && ft_strcmp(paths[i], paths[j]) == 0)
				ft_kill(data, ERR_DUPLICATION);
			j++;
		}
		i++;
	}
}

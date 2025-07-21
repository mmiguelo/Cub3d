#include "cub3D.h"

void	check_textures(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		insert_texture(data, &data->textures.north.path, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		insert_texture(data, &data->textures.south.path, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		insert_texture(data, &data->textures.west.path, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		insert_texture(data, &data->textures.east.path, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		insert_rgb(data, &data->floor, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		insert_rgb(data, &data->ceiling, line, &i);
}

void	insert_texture(t_data *data, char **path, char *line, int *i)
{
	int len;

	*i += 2;
	while (line[*i] == ' ')
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

void	check_duplicated_textures(t_textures *textures)
{
	if (textures->north.path && textures->south.path
		&& ft_strcmp(textures->north.path, textures->south.path) == 0)
		ft_kill(NULL, ERR_DUPLICATION);
	if (textures->north.path && textures->west.path
		&& ft_strcmp(textures->north.path, textures->west.path) == 0)
		ft_kill(NULL, ERR_DUPLICATION);
	if (textures->north.path && textures->east.path
		&& ft_strcmp(textures->north.path, textures->east.path) == 0)
		ft_kill(NULL, ERR_DUPLICATION);
	if (textures->south.path && textures->west.path
		&& ft_strcmp(textures->south.path, textures->west.path) == 0)
		ft_kill(NULL, ERR_DUPLICATION);
	if (textures->south.path && textures->east.path
		&& ft_strcmp(textures->south.path, textures->east.path) == 0)
		ft_kill(NULL, ERR_DUPLICATION);
	if (textures->west.path && textures->east.path
		&& ft_strcmp(textures->west.path, textures->east.path) == 0)
		ft_kill(NULL, ERR_DUPLICATION);
}

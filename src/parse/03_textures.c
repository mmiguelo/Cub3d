#include "cub3D.h"

void	assign_texture(t_data *data, char **path, char *line, int *i)
{
	/* int	len; */
	char	*trimed;

	trimed = NULL;
	*i += 2;
	while (ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] == '\0')
		ft_kill(data, ERR_TEXTURE);
	if (*path)
		ft_kill(data, ERR_DUPLICATION);
	*path = ft_strdup(&line[*i]);
	if (!*path)
		ft_kill(data, ERR_MALLOC);
	if (!path)
		ft_kill(data, ERR_MALLOC);
	trimed = ft_strtrim(*path, WS);
	free(*path);
	*path = trimed;
/* 	len = ft_strlen(*path);
	if (len > 0 && (*path)[len - 1] == '\n')
		(*path)[len - 1] = '\0'; */
	check_extension_texture(data, *path, ".xpm");
}

void	check_required_textures(t_data *data, t_textures *textures)
{
	if (!textures->north.path)
		ft_kill(data, ERR_TEXTURE);
	if (!textures->south.path)
		ft_kill(data, ERR_TEXTURE);
	if (!textures->west.path)
		ft_kill(data, ERR_TEXTURE);
	if (!textures->east.path)
		ft_kill(data, ERR_TEXTURE);
}

int	is_all_assets(t_data *data)
{
	if (!data)
		return (0);
	if (!data->textures.north.path || !data->textures.south.path
		|| !data->textures.west.path || !data->textures.east.path)
		return (0);
	if (data->floor.r == -1 || data->floor.g == -1 || data->floor.b == -1)
		return (0);
	if (data->ceiling.r == -1 || data->ceiling.g == -1
		|| data->ceiling.b == -1)
		return (0);
	return (1);
}

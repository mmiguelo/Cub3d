#include "cub3D.h"

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
	if (!*path)
		ft_kill(data, ERR_MALLOC);
	if (!path)
		ft_kill(data, ERR_MALLOC);
	len = ft_strlen(*path);
	if (len > 0 && (*path)[len - 1] == '\n')
		(*path)[len - 1] = '\0';
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

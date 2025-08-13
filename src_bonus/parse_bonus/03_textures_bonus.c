/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:00:25 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/13 13:00:26 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	assign_texture(t_data *data, char **path, char *line, int *i)
{
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
	trimed = ft_strtrim(*path, WS);
	free(*path);
	*path = trimed;
	parse(data, *path, ".xpm");
}

void	check_required_textures(t_data *data, t_textures textures)
{
	if (!textures.north.path)
		ft_kill(data, ERR_TEXTURE_MISSING);
	if (!textures.south.path)
		ft_kill(data, ERR_TEXTURE_MISSING);
	if (!textures.west.path)
		ft_kill(data, ERR_TEXTURE_MISSING);
	if (!textures.east.path)
		ft_kill(data, ERR_TEXTURE_MISSING);
}

int	is_all_assets(t_data *data)
{
	if (!data)
		return (0);
	if (!data->textures.north.path)
		return (0);
	if (!data->textures.south.path)
		return (0);
	if (!data->textures.west.path)
		return (0);
	if (!data->textures.east.path)
		return (0);
	if (data->floor.r == -1 && data->floor.g == -1 && data->floor.b == -1)
		return (0);
	if (data->ceiling.r == -1 && data->ceiling.g == -1
		&& data->ceiling.b == -1)
		return (0);
	return (1);
}

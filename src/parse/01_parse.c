/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:00:33 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/13 13:00:33 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse(t_data *data, char *filename, char *extension)
{
	check_extension(data, filename, extension);
	check_directory(data, filename);
	if (access(filename, F_OK | R_OK) == -1)
		ft_kill(data, ERR_FILE);
}

void	check_assets(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && ft_isspace(line[i + 2]))
		assign_texture(data, &data->textures.north.path, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2]))
		assign_texture(data, &data->textures.south.path, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2]))
		assign_texture(data, &data->textures.west.path, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2]))
		assign_texture(data, &data->textures.east.path, line, &i);
	else if (line[i] == 'F' && ft_isspace(line[i + 1]))
		assign_rgb(data, &data->floor, line);
	else if (line[i] == 'C' && ft_isspace(line[i + 1]))
		assign_rgb(data, &data->ceiling, line);
}

void	parse_file_content(t_data *data, char *filename)
{
	int	i;

	i = -1;
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0)
		ft_kill(NULL, ERR_FILE);
	data->line = get_next_line(data->fd);
	if (!data->line)
		ft_kill(NULL, ERR_EMPTY);
	while (data->line)
	{
		process_line(data, data->line, &i);
		free(data->line);
		data->line = get_next_line(data->fd);
	}
	close(data->fd);
	check_required_textures(data, data->textures);
	check_map_walls_and_player(data, &data->map);
	check_duplicated_color(data, &data->ceiling, &data->floor);
}

void	process_line(t_data *data, char *line, int *i)
{
	if (ft_has_white_spaces(line))
	{
		if (data->map.started)
			data->map.ended = true;
		return ;
	}
	if (is_all_assets(data))
		check_map(data, &data->map, line, ++(*i));
	else
		check_assets(data, line);
}

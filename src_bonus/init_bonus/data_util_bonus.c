/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_util_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:28:01 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/25 18:28:01 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_textures(t_data *data)
{
	load_textures(data, &data->textures.north);
	load_textures(data, &data->textures.south);
	load_textures(data, &data->textures.east);
	load_textures(data, &data->textures.west);
}

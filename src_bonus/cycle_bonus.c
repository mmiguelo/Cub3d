/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:54:38 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/23 23:54:38 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/* bool	is_night(t_data *data)
{
	return (data->global_light <= NIGHT_END);
} */

void	render_cycle(t_data *data)
{
	if (data->bsunrise)
		mlx_put_image_to_window(data->mlx, data->win, data->sunrise.img,
			WIN_WIDTH - 125, 60);
	else if (data->bsun)
		mlx_put_image_to_window(data->mlx, data->win, data->sun.img,
			WIN_WIDTH - 125, 60);
	else if (data->bsunset)
		mlx_put_image_to_window(data->mlx, data->win, data->sunset.img,
			WIN_WIDTH - 125, 60);
	else
		mlx_put_image_to_window(data->mlx, data->win, data->moon.img,
			WIN_WIDTH - 125, 60);
}

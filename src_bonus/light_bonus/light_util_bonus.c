/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 22:10:19 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/25 22:10:19 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	change_day(bool *to_false, bool *to_true)
{
	*to_false = false;
	*to_true = true;
}

int	lerp_color(int start, int end, double t)
{
	int	r;
	int	g;
	int	b;

	r = ((start >> 16) & 0xFF) * (1 - t) + ((end >> 16) & 0xFF) * t;
	g = ((start >> 8) & 0xFF) * (1 - t) + ((end >> 8) & 0xFF) * t;
	b = (start & 0xFF) * (1 - t) + (end & 0xFF) * t;
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

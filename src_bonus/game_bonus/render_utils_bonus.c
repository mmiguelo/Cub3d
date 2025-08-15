/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:01:40 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/14 23:01:40 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	color(t_draw *draw, t_img *texture)
{
	return (*(int *)(texture->addr + (draw->tex_y * texture->line_length
			+ draw->tex_x * (texture->bits_per_pixel / 8))));
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (y < 0 || y > WIN_HEIGHT - 1 || x < 0
		|| x > WIN_WIDTH - 1)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	copy_bg_to_image(t_img *bg, t_img *image)
{
    int x, y;
    char *src;
    char *dst;

    for (y = 0; y < bg->height; y++)
    {
        for (x = 0; x < bg->width; x++)
        {
            src = bg->addr + (y * bg->line_length + x * (bg->bits_per_pixel / 8));
            dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
            *(unsigned int *)dst = *(unsigned int *)src;
        }
    }
}

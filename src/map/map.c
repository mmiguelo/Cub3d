#include "cub3D.h"

void	game_loop(t_data *data)
{
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, x_press, data);
	mlx_loop_hook(data->mlx, &draw_loop, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_hook_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_hook_release, data);
	mlx_loop(data->mlx);
}

int	draw_loop(t_data *data)
{
	calculate_movements(data);
	calculate_raycasting(data);
	return (0);
}

void	calculate_raycasting(t_data *data)
{
	t_ray	ray;
	int x;

	x = 0;
	put_fc(data);
	while(x < WIN_WIDTH)
	{
		ray.draw.hit = false;
		calculate_variables(&data->player, &ray, x);
		while (ray.draw.hit == false)
			check_hit(data, &ray);
		calculate_perpwalldist(&ray, &ray.draw);
		calculate_texture(data, &ray);
		while (ray.draw.start < ray.draw.end)
			draw_line(data, &ray, x);
		x += 1;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->bg.img, 0, 0);
}

void	put_fc(t_data *data)
{
	int x, y;
	char *pixel_addr;
	int color;

	for (y = 0; y < WIN_HEIGHT; y++)
	{
		for (x = 0; x < WIN_WIDTH; x++)
		{
			if (y < WIN_HEIGHT / 2)
			{
				color = (data->ceiling.r << 16) | (data->ceiling.g << 8)
				| data->ceiling.b;
			}
			else
			{
				color = (data->floor.r << 16) | (data->floor.g << 8)
					| data->floor.b;
			}
			pixel_addr = data->bg.addr + (y * data->bg.line_length) 
				+ (x * (data->bg.bits_per_pixel / 8));
			*(unsigned int *)pixel_addr = color;
		}
	}
}

void	calculate_variables(t_player *player, t_ray *ray, int x)
{
	ray->pos.x = (int)player->x;
	ray->pos.y = (int)player->y;
	ray->cam.screen_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir.x = player->dir.x + player->plane.x * ray->cam.screen_x;
	ray->dir.y = player->dir.y + player->plane.y * ray->cam.screen_x;
	if (ray->dir.x == 0)
		ray->step.delta_dist_x = 1e30;
	else
		ray->step.delta_dist_x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->step.delta_dist_y = 1e30;
	else
		ray->step.delta_dist_y = fabs(1 / ray->dir.y);
	calculate_variables2(ray, player->x, player->y);
}

void	calculate_variables2(t_ray *ray, double player_x, double player_y)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->step.side_dist_x = (player_x - ray->pos.x)
			* ray->step.delta_dist_x;
	}
	else
	{
		ray->step.x = 1;
		ray->step.side_dist_x = (ray->pos.x + 1.0 - player_x)
			* ray->step.delta_dist_x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->step.side_dist_y = (player_y - ray->pos.y)
			* ray->step.delta_dist_y;
	}
	else
	{
		ray->step.y = 1;
		ray->step.side_dist_y = (ray->pos.y + 1.0 - player_y) 
			* ray->step.delta_dist_y;
	}
}

void	check_hit(t_data *data, t_ray *ray)
{
	if (ray->step.side_dist_x < ray->step.side_dist_y)
	{
		ray->step.side_dist_x += ray->step.delta_dist_x;
		ray->pos.x += ray->step.x;
		ray->draw.side = 0;
	}
	else
	{
		ray->step.side_dist_y += ray->step.delta_dist_y;
		ray->pos.y += ray->step.y;
		ray->draw.side = 1;
	}
	if (ray->pos.x >= 0 && ray->pos.x < data->map.width
		&& ray->pos.y >= 0 && ray->pos.y < data->map.height)
	{
		if (data->map.grid[ray->pos.y][ray->pos.x] == '1')
			ray->draw.hit = true;
		else if (data->map.grid[ray->pos.y][ray->pos.x] == '0')
			ray->draw.hit = false;
	}
	else
		ray->draw.hit = true; // evita segfault por sair fora do mapa
}

void	calculate_perpwalldist(t_ray *ray, t_draw *draw)
{
	if (draw->side == 0)
		draw->perpWallDist = ray->step.side_dist_x - ray->step.delta_dist_x;
	else
		draw->perpWallDist = ray->step.side_dist_y - ray->step.delta_dist_y;
	draw->line_height = (int)(WIN_HEIGHT / draw->perpWallDist);
	draw->start = -draw->line_height / 2 + WIN_HEIGHT / 2 + PITCH;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_height / 2 + WIN_HEIGHT / 2 + PITCH;
	if (draw->end >= WIN_HEIGHT)
		draw->end = WIN_HEIGHT - 1;
}
void	calculate_texture(t_data *data, t_ray *ray)
{
	if (ray->draw.side == 0)
		ray->draw.wallX = data->player.y + ray->draw.perpWallDist * ray->dir.y;
	else
		ray->draw.wallX = data->player.x + ray->draw.perpWallDist * ray->dir.x;
	ray->draw.wallX -= floor(ray->draw.wallX);
	ray->draw.texX = (int)(ray->draw.wallX * TILE_SIZE);
	if (ray->draw.side == 0 && ray->dir.x > 0)
		ray->draw.texX = TILE_SIZE - ray->draw.texX - 1;
	if (ray->draw.side == 1 && ray->dir.y < 0)
		ray->draw.texX = TILE_SIZE - ray->draw.texX - 1;
	ray->draw.step = 1.0 * TILE_SIZE / ray->draw.line_height;
	ray->draw.texPos = (ray->draw.start - PITCH - WIN_HEIGHT / 2
		+ ray->draw.line_height / 2) * ray->draw.step;
}

void	draw_line(t_data *data, t_ray *ray, int x)
{
	ray->draw.texY = ray->draw.texPos;
	ray->draw.texPos += ray->draw.step;
	if (ray->draw.side == 0 && ray->dir.x > 0)
		ray->draw.color = color(&ray->draw, &data->textures.west);
	else if (ray->draw.side == 0 && ray->dir.x < 0)
		ray->draw.color = color(&ray->draw, &data->textures.east);
	else if (ray->draw.side == 1 && ray->dir.y > 0)
		ray->draw.color = color(&ray->draw, &data->textures.south);
	else
		ray->draw.color = color(&ray->draw, &data->textures.north);
	put_pixel(&data->bg, x, ray->draw.start, ray->draw.color);
	ray->draw.start++;
}

int	color(t_draw *draw, t_img *texture)
{
	return (*(int *)(texture->addr + (draw->texY * texture->line_length
		+ draw->texX * (texture->bits_per_pixel / 8))));
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

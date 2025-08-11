#include "cub3D.h"

void	game_loop(t_data *data, t_ray *ray)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_kill(data, ERR_MLX);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
		ft_kill(data, ERR_MLX_WIN);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, x_press, data);
	mlx_loop_hook(data->mlx, (int (*)(void *))draw_loop, data);
	mlx_loop(data->mlx);
}

void	draw_loop(void *param)
{
	t_data	*data;
	t_ray	*ray;
	int x;

	data = (t_data *)param;
	ray = &data->ray;
	x = 0;
	while(x < WIN_WIDTH)
	{
		ray->draw.hit = false;
		calculate_variables(data->player, ray, x);
		while (ray->draw.hit == false)
			check_hit(data, ray);
		calculate_perpwalldist(data, ray, &ray->draw);
		x++;
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
	if (data->map.grid[ray->pos.x][ray->pos.y] != 0)
		ray->draw.hit = true;
}

void	calculate_perpwalldist(t_data *data, t_ray *ray, t_draw *draw)
{
	if (draw.side == 0)
		draw->perpWallDist = (ray->step.side_dist_x - ray->step.delta_dist_x);
	else
		draw->perpWallDist = (ray->step.side_dist_y - ray->step.delta_dist_y);
	draw->line_height = (int)(WIN_HEIGHT / draw->perpWallDist);
	draw->start = -draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->end >= WIN_HEIGHT)
		draw->end = WIN_HEIGHT - 1;
}
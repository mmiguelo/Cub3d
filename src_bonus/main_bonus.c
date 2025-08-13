/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:59:01 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/08/13 14:23:07 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		ft_kill(NULL, ERR_ARGS);
	init(&data);
	parse(&data, av[1], ".cub");
	parse_file_content(&data, av[1]);
	get_player_vector(&data);
	game_loop(&data);
	return (0);
}

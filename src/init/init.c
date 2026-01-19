/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeer42 <abeer42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2026/01/13 23:23:58 by abeer42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init(t_cub *cub)
{
	cub->fd = -1;
	cub->line = NULL;
	cub->file_name = NULL;
	cub->map = NULL;
	cub->map_w = 0;
	cub->map_h = 0;
	cub->player_dir = '\0';
	cub->mlx = NULL;
	cub->img = NULL;
	cub->west_t = NULL;
	cub->east_t = NULL;
	cub->south_t = NULL;
	cub->north_t = NULL;
	cub->frame = 0;
	cub->test_mode = 0;
	cub->error_code = 0;
	cub->error_message = NULL;
	cub->keys.w = false;
	cub->keys.s = false;
	cub->keys.a = false;
	cub->keys.d = false;
	cub->keys.r = false;
	cub->keys.l = false;
	cub->data = NULL;
}

void	init_data(t_cub *game)
{
	game->data->ceil = 0;
	game->data->floor = 0;
	game->data->ceil_str = NULL;
	game->data->floor_str = NULL;
	game->data->player_x = -1;
	game->data->player_y = -1;
	game->data->pov = 0;
	game->data->no = NULL;
	game->data->so = NULL;
	game->data->ea = NULL;
	game->data->we = NULL;
}

void	init_cub(int ac, char **av, t_cub *cub)
{
	init(cub);
	cub->data = ft_calloc(1, sizeof(t_data));
	if (!cub->data)
		ft_exit(cub, "malloc failed", MALLOC_FAILED); // ??
	init_data(cub);
	check_input(ac, av, cub);
	check_file(cub);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeer42 <abeer42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2026/01/12 18:09:30 by abeer42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	define_initial_plane(t_cub *game)
{
	if (game->data->pov == 'N')
	{
		game->dir = create_vector(0, -1);
		game->camera_plane = create_vector(0.66, 0);
	}
	else if (game->data->pov == 'S')
	{
		game->dir = create_vector(0, 1);
		game->camera_plane = create_vector(-0.66, 0);
	}
	else if (game->data->pov == 'W')
	{
		game->dir = create_vector(-1, 0);
		game-> camera_plane = create_vector(0, -0.66);
	}
	else if (game->data->pov == 'E')
	{
		game->dir = create_vector(1, 0);
		game->camera_plane = create_vector(0, 0.66);
	}
}

void	setup(t_cub *game)
{
	game->pos = create_vector(game->data->player_x + 0.5,
			game->data->player_y + 0.5);
}

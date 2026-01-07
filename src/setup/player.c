/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector	create_vector(double x, double y)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	return (v);
}

static void define_plane(t_cub *game)
{
    if (game->data->pov_player == 'N')
    {
        game->dir = create_vector(0, -1);
        game->cam_plane = create_vector(0.66, 0);
    }
    else if (game->data->pov_player == 'S')
    {
        game->dir = create_vector(0, 1);
        game->cam_plane = create_vector(-0.66, 0);
    }
    else if (game->data->pov_player == 'W')
    {
        game->dir = create_vector(-1, 0);
        game->cam_plane = create_vector(0, -0.66);
    }
    else if (game->data->pov_player == 'E')
    {
        game->dir = create_vector(1, 0);
        game->cam_plane = create_vector(0, 0.66);
    }
}

void	setup(t_cub *game)
{
	game->pos = create_vector(game->data->player_x + 0.5,
			game->data->player_y + 0.5);
	define_plane(game);
}

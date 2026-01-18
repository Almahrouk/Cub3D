/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 10:35:02 by aal-joul          #+#    #+#             */
/*   Updated: 2026-01-18 10:35:02 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_signal(float v)
{
	if (v < 0)
		return (-1);
	return (1);
}

void	calculate_new_pos(t_cub *game, float *new_x, float *new_y)
{
	float	move_speed;

	move_speed = game->frame * 4;
	*new_x = game->pos.x;
	*new_y = game->pos.y;
	if (game->keys.w == true)
	{
		*new_x += game->dir.x * move_speed;
		*new_y += game->dir.y * move_speed;
	}
	if (game->keys.s == true)
	{
		*new_x -= game->dir.x * move_speed;
		*new_y -= game->dir.y * move_speed;
	}
	if (game->keys.a == true)
	{
		*new_x -= game->camera_plane.x * move_speed;
		*new_y -= game->camera_plane.y * move_speed;
	}
	if (game->keys.d == true)
	{
		*new_x += game->camera_plane.x * move_speed;
		*new_y += game->camera_plane.y * move_speed;
	}
}

bool	can_move_to(t_cub *game, float new_x, float new_y)
{
	float	margin;

	margin = 0.1;
	if (game->map[(int)(new_y + margin
			* get_signal(new_y - game->pos.y))][(int)new_x] == '1')
		return (false);
	if (game->map[(int)new_y][(int)(new_x + margin
		* get_signal(new_x - game->pos.x))] == '1')
		return (false);
	if (game->map[(int)(new_y + margin
			* get_signal(game->camera_plane.y))][(int)new_x] == '1')
		return (false);
	if (game->map[(int)new_y][(int)(new_x + margin
		* get_signal(game->camera_plane.x))] == '1')
		return (false);
	return (true);
}

void	try_move(t_cub *game, float new_x, float new_y)
{
	float	margin;

	margin = 0.1;
	if (game->map[(int)(game->pos.y)]
		[(int)(new_x + margin * get_signal(new_x - game->pos.x))] != '1')
	{
		game->pos.x = new_x;
	}
	if (game->map[(int)(new_y + margin * get_signal(new_y - game->pos.y))]
		[(int)(game->pos.x)] != '1')
	{
		game->pos.y = new_y;
	}
}

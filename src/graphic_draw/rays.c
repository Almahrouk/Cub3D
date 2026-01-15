/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	set_dir(float dir)
{
	if (dir < 0)
		return (-1);
	return (1);
}

void	calculate_delta_dist(t_dda *ray)
{
	if (ray->dir.x == 0)
		ray->delta_dist.x = HUGE_VALF;
	else
		ray->delta_dist.x = fabsf(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = HUGE_VALF;
	else
		ray->delta_dist.y = fabsf(1 / ray->dir.y);
}

void	calculate_dist_2side(t_cub *game, t_dda *ray)
{
	ray->map.x = game->pos.x;
	ray->map.y = game->pos.y;
	if (ray->dir.x < 0)
		ray->dist_side.x = (game->pos.x - ray->map.x) * ray->delta_dist.x;
	else
	{
		ray->dist_side.x = (ray->map.x + 1.0 - game->pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
		ray->dist_side.y = (game->pos.y - ray->map.y) * ray->delta_dist.y;
	else
	{
		ray->dist_side.y = (ray->map.y + 1.0 - game->pos.y)
			* ray->delta_dist.y;
	}
}

void	dda_algo(t_cub *game, t_dda *ray)
{
	while (game->data->map[ray->map.y][ray->map.x] != '1')
	{
		if (ray->dist_side.x < ray->dist_side.y)
		{
			ray->dist_side.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->hit_side = 0;
			game->hit_side = 0;
		}
		else
		{
			ray->dist_side.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->hit_side = 1;
			game->hit_side = 1;
		}
	}
	if (ray->hit_side == 0)
		ray->perp_dist = ray->dist_side.x - ray->delta_dist.x;
	else
		ray->perp_dist = ray->dist_side.y - ray->delta_dist.y;
}

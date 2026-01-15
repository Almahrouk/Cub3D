/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	intersection_point(t_cub *game, t_dda *ray, t_wall *wall)
{
	if (ray->hit_side == 0)
		wall->point_x = game->pos.y + ray->perp_dist * ray->dir.y;
	else
		wall->point_x = game->pos.x + ray->perp_dist * ray->dir.x;
	wall->point_x -= floor(wall->point_x);
}

static void	find_tex_position_x(t_cub *game, t_dda *ray, t_wall *wall)
{
	wall->tex_x = (int)(wall->point_x * game->texture->width);
	if ((ray->hit_side == 0 && ray->dir.x < 0)
		|| (ray->hit_side == 1 && ray->dir.y > 0))
		wall->tex_step = 1.0 * game->texture->height / wall->h;
}

static void	render_wall(t_cub *game, t_wall *wall, int pix)
{
	int			y;
	int			tex_y;
	uint32_t	color;

	y = wall->start_y;
	while (y < wall->end_y)
	{
		tex_y = (int)wall->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)game->texture->height)
			tex_y = game->texture->height -1;
		wall->tex_pos += wall->tex_step;
		color = get_tex_color(game->texture, tex_y, wall->tex_x);
		mlx_put_pixel(game->img, pix, y, color);
		y++;
	}
}

mlx_texture_t	*set_wall(t_cub *game, t_dda *ray)
{
	if (ray->hit_side == 1)
	{
		if (ray->step.y < 0)
			return (game->north_t);
		else
			return (game->south_t);
	}
	else
	{
		if (ray->step.x < 0)
			return (game->west_t);
		else
			return (game->east_t);
	}
	return (NULL);
}

void	draw_wall(t_cub *game, t_dda *ray, int pix)
{
	t_wall	wall;

	game->texture = set_wall(game, ray);
	wall.h = (WIN_H / ray->perp_dist);
	wall.start_y = (WIN_H / 2 - wall.h / 2);
	wall.end_y = (WIN_H / 2 + wall.h / 2);
	if (wall.start_y < 0)
		wall.start_y = 0;
	if (wall.end_y >= WIN_H)
		wall.end_y >= WIN_H - 1;
	intersection_point(game, ray, &wall);
	find_tex_position_x(game, ray, &wall);
	wall.tex_pos = (wall.start_y - WIN_H / 2 + wall.h / 2)
		*wall.tex_step;
	render_wall(game, &wall, pix);
}

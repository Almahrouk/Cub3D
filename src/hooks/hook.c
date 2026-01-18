/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	release(mlx_key_data_t key_p, t_cub *game);
static void	pressed(mlx_key_data_t key_p, t_cub *game);

void	hook_key_press(mlx_key_data_t key_p, void *p)
{
	t_cub	*game;

	game = (t_cub *) p;
	if (key_p.key == MLX_KEY_ESCAPE && key_p.action == MLX_PRESS)
	{
		hook_close(game);
		return ;
	}
	if (key_p.action == MLX_PRESS || key_p.action == MLX_REPEAT)
		pressed(key_p, game);
	else if (key_p.action == MLX_RELEASE)
		release(key_p, game);
}

void	hook_close(void *p)
{
	t_cub	*game;

	if (!p)
		exit(0);
	game = (t_cub *) p;
	if (game->mlx)
		mlx_close_window(game->mlx);
}

static void	pressed(mlx_key_data_t key_p, t_cub *game)
{
	if (key_p.key == MLX_KEY_W)
		game->keys.w = true;
	else if (key_p.key == MLX_KEY_A)
		game->keys.a = true;
	else if (key_p.key == MLX_KEY_D)
		game->keys.d = true;
	else if (key_p.key == MLX_KEY_S)
		game->keys.s = true;
	else if (key_p.key == MLX_KEY_LEFT)
		game->keys.l = true;
	else if (key_p.key == MLX_KEY_RIGHT)
		game->keys.r = true;
}

static void	release(mlx_key_data_t key_p, t_cub *game)
{
	if (key_p.key == MLX_KEY_W)
		game->keys.w = false;
	else if (key_p.key == MLX_KEY_A)
		game->keys.a = false;
	else if (key_p.key == MLX_KEY_D)
		game->keys.d = false;
	else if (key_p.key == MLX_KEY_S)
		game->keys.s = false;
	else if (key_p.key == MLX_KEY_LEFT)
		game->keys.l = false;
	else if (key_p.key == MLX_KEY_RIGHT)
		game->keys.r = false;
}

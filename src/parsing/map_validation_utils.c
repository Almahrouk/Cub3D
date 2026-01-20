/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_player_tile(t_cub *cub, int x, int y, int *player_count)
{
	if (x == 0 || y == 0 || x == cub->map_w - 1 || y == cub->map_h - 1)
		map_error(cub, "Error\nplayer on edge\n");
	(*player_count)++;
	cub->data->player_x = x;
	cub->data->player_y = y;
	cub->player_dir = cub->map[y][x];
	cub->data->pov = cub->map[y][x];
	cub->map[y][x] = '0';
}

void	check_map_tile(t_cub *cub, int x, int y, int *player_count)
{
	char	c;

	c = cub->map[y][x];
	if (!is_map_char(c))
		map_error(cub, "Error\ninvalid map character\n");
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		handle_player_tile(cub, x, y, player_count);
}

void	check_map_content(t_cub *cub)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < cub->map_h)
	{
		x = 0;
		while (x < cub->map_w)
		{
			check_map_tile(cub, x, y, &player_count);
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		map_error(cub, "Error\ninvalid player count\n");
	}
}

int	is_invalid_neighbor(t_cub *cub, int x, int y)
{
	if (x == 0 || y == 0)
		return (1);
	if (x == cub->map_w - 1 || y == cub->map_h - 1)
		return (1);
	if (cub->map[y][x - 1] == ' ')
		return (1);
	if (cub->map[y][x + 1] == ' ')
		return (1);
	if (cub->map[y - 1][x] == ' ')
		return (1);
	if (cub->map[y + 1][x] == ' ')
		return (1);
	return (0);
}

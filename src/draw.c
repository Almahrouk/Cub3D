/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_square(t_cub *cub, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(cub->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_cub *cub)
{
	int		y;
	int		x;
	char	**map;

	map = cub->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(cub, x * TILE_SIZE, y * TILE_SIZE, 0x808080FF);
			else
				draw_square(cub, x * TILE_SIZE, y * TILE_SIZE, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
	draw_square(cub, (int)(cub->player_x * TILE_SIZE),
		(int)(cub->player_y * TILE_SIZE), 0xFF0000FF);
}

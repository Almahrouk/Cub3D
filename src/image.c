/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

mlx_texture_t	*init_tex(char *path)
{
	mlx_texture_t	*img;

	img = mlx_load_png(path);
	if (!img)
		return (NULL);
	return (img);
}

void	load_tex(t_cub *game)
{
	game->north = init_tex(game->data->no);
	game->south = init_tex(game->data->so);
	game->west = init_tex(game->data->we);
	game->east = init_tex(game->data->ea);
}

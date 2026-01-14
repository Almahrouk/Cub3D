/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeer42 <abeer42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2026/01/11 23:48:02 by abeer42          ###   ########.fr       */
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
	game->north_t = init_tex(game->data->no);
	game->south_t = init_tex(game->data->so);
	game->west_t = init_tex(game->data->we);
	game->east_t = init_tex(game->data->ea);
	if (!game->north_t || !game->south_t || !game->west_t || !game->east_t)
    	ft_exit(game, "Error\nfailed to load textures\n", FAILD);
}

uint32_t	get_tex_color(mlx_texture_t *tex, int y, int x)
{
	int		tex_pos;
	uint8_t	*pixel;
	
	if (x < 0 || x >= (int)tex->width || y < 0
		|| y >= (int)tex->height)
		return (0);
	tex_pos = y * tex->width + x;
	tex_pos *= tex->bytes_per_pixel;
	pixel = &tex->pixels[tex_pos];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}
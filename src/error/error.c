/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	destroy_textures(t_cub *game)
{
	if (game->north_t)
		mlx_delete_texture(game->north_t);
	if (game->south_t)
		mlx_delete_texture(game->south_t);
	if (game->west_t)
		mlx_delete_texture(game->west_t);
	if (game->east_t)
		mlx_delete_texture(game->east_t);
	game->north_t = NULL;
	game->south_t = NULL;
	game->west_t = NULL;
	game->east_t = NULL;
}

static void	ft_free(t_cub *cub, char *message, int err_no)
{
	if (cub && cub->test_mode)
	{
		cub->error_message = ft_strdup(message);
		cub->error_code = err_no;
		return ;
	}
	if (cub && cub->data)
	{
		free(cub->data->floor_str);
		free(cub->data->ceil_str);
		free(cub->data->no);
		free(cub->data->so);
		free(cub->data->ea);
		free(cub->data->we);
		free(cub->data);
		cub->data = NULL;
	}
	free_map(cub->map);
	cub->map = NULL;
	perror(message);
}

void	ft_exit(t_cub *cub, char *message, int err_no)
{
	ft_free(cub, message, err_no);
	exit(err_no);
}

void	ft_exit_game(t_cub *cub, char *message, int err_no)
{
	ft_free(cub, message, err_no);
	destroy_textures(cub);
	if (cub->img)
	{
		mlx_delete_image(cub->mlx, cub->img);
		cub->img = NULL;
	}
	if (cub->mlx)
	{
		mlx_terminate(cub->mlx);
		cub->mlx = NULL;
	}
	exit(err_no);
}

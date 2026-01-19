/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 11:02:54 by aal-joul          #+#    #+#             */
/*   Updated: 2026-01-18 11:02:54 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_cub *cub)
{
	int	i;

	if (!cub || !cub->map)
		return ;
	i = 0;
	while (i < cub->map_h)
	{
		free(cub->map[i]);
		i++;
	}
	free(cub->map);
	cub->map = NULL;
}

void	free_data(t_cub *cub)
{
	if (!cub || !cub->data)
		return ;
	free(cub->data->no);
	free(cub->data->so);
	free(cub->data->we);
	free(cub->data->ea);
	free(cub->data->floor_str);
	free(cub->data->ceil_str);
	free(cub->data);
	cub->data = NULL;
}

void	free_textures(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->north_t)
		mlx_delete_texture(cub->north_t);
	if (cub->south_t)
		mlx_delete_texture(cub->south_t);
	if (cub->west_t)
		mlx_delete_texture(cub->west_t);
	if (cub->east_t)
		mlx_delete_texture(cub->east_t);
	cub->north_t = NULL;
	cub->south_t = NULL;
	cub->west_t = NULL;
	cub->east_t = NULL;
}

void	free_mlx(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->img)
	{
		mlx_delete_image(cub->mlx, cub->img);
		cub->img = NULL;
	}
	cub->img = NULL;
	if (cub->mlx)
	{
		mlx_terminate(cub->mlx);
		cub->mlx = NULL;
	}
	cub->mlx = NULL;
}

void	free_memory(t_cub *cub)
{
	if (!cub)
		return ;
	free_map(cub);
	free_data(cub);
	free_textures(cub);
	free_mlx(cub);
	if (cub->line)
		free(cub->line);
	cub->line = NULL;
	if (cub->fd >= 0)
		close(cub->fd);
	gnl_cleanup();
	free(cub);
}

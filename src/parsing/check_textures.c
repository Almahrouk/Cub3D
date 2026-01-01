/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_textures_paths(t_cub *cub, char *path, char *message)
{
	if (ft_strncmp(path + ft_strlen(path) - 4, ".png", 4) != 0
		&& ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) != 0)
		ft_exit(cub, message, TEXTURE_PATH_ERROR);
}

void	check_textures_open(t_cub *cub, char *path, char *msg)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit(cub, msg, TEXTURE_OPEN_ERROR);
	close(fd);
}

void	check_duplicates(t_cub *cub)
{
	if (strcmp(cub->north_path, cub->south_path) == 0
		|| strcmp(cub->north_path, cub->west_path) == 0
		|| strcmp(cub->north_path, cub->east_path) == 0
		|| strcmp(cub->south_path, cub->west_path) == 0
		|| strcmp(cub->south_path, cub->east_path) == 0
		|| strcmp(cub->west_path, cub->east_path) == 0)
		ft_exit(cub, "Error\nduplicate texture paths\n", TEXTURE_PATH_ERROR);
}

static void	check_texture_files(t_cub *cub)
{
	check_textures_paths(cub, cub->north_path,
		"Error\nnorth texture must be .png or .xpm\n");
	check_textures_paths(cub, cub->south_path,
		"Error\nsouth texture must be .png or .xpm\n");
	check_textures_paths(cub, cub->west_path,
		"Error\nwest texture must be .png or .xpm\n");
	check_textures_paths(cub, cub->east_path,
		"Error\neast texture must be .png or .xpm\n");
	check_duplicates(cub);
	if (!cub->test_mode)
	{
		check_textures_open(cub, cub->north_path, "Error\nopening north texture\n");
		check_textures_open(cub, cub->south_path, "Error\nopening south texture\n");
		check_textures_open(cub, cub->west_path, "Error\nopening west texture\n");
		check_textures_open(cub, cub->east_path, "Error\nopening east texture\n");
		printf("All textures are valid and accessible.\n");
	}
}

void	check_textures(t_cub *cub)
{
	if (!cub->north_path || !cub->south_path
		|| !cub->west_path || !cub->east_path
		|| !cub->floor_color || !cub->ceiling_color)
		ft_exit(cub, "Error\nmissing texture path(s) or color(s)\n",
			MISSING_TEXTURE_ERROR);
	check_texture_files(cub);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeer42 <abeer42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2026/01/13 23:18:57 by abeer42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_textures_paths(t_cub *cub, char *path, char *message)
{
	//⚠️ Risky if path == NULL
	//⚠️ Risky if path shorter than 4 chars
	/*
	if (!path || ft_strlen(path) < 4)
		ft_exit(cub, message, TEXTURE_PATH_ERROR);
	*/
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
	if (strcmp(cub->data->no, cub->data->so) == 0
		|| strcmp(cub->data->no, cub->data->we) == 0
		|| strcmp(cub->data->no, cub->data->ea) == 0
		|| strcmp(cub->data->so, cub->data->we) == 0
		|| strcmp(cub->data->so, cub->data->ea) == 0
		|| strcmp(cub->data->we, cub->data->ea) == 0)
		ft_exit(cub, "Error\nduplicate texture paths\n", TEXTURE_PATH_ERROR);
}

static void	check_texture_files(t_cub *cub)
{
	check_textures_paths(cub, cub->data->no ,
		"Error\nnorth texture must be .png or .xpm\n");
	check_textures_paths(cub, cub->data->so,
		"Error\nsouth texture must be .png or .xpm\n");
	check_textures_paths(cub, cub->data->we,
		"Error\nwest texture must be .png or .xpm\n");
	check_textures_paths(cub, cub->data->ea,
		"Error\neast texture must be .png or .xpm\n");
	check_duplicates(cub);
	if (!cub->test_mode)
	{
		check_textures_open(cub, cub->data->no, "Error\nopening north texture\n");
		check_textures_open(cub, cub->data->so, "Error\nopening south texture\n");
		check_textures_open(cub, cub->data->we, "Error\nopening west texture\n");
		check_textures_open(cub, cub->data->ea, "Error\nopening east texture\n");
		//printf("All textures are valid and accessible.\n");
	}
}

void	check_textures(t_cub *cub)
{
	if (!cub->data->no || !cub->data->so
		|| !cub->data->we || !cub->data->ea
		|| !cub->data->floor_str || !cub->data->ceil_str)
		ft_exit(cub, "Error\nmissing texture path(s) or color(s)\n",
			MISSING_TEXTURE_ERROR);
	cub->data->floor = parse_rgb(cub, cub->data->floor_str);
	cub->data->ceil = parse_rgb(cub, cub->data->ceil_str);
	free(cub->data->floor_str);
	free(cub->data->ceil_str);
	cub->data->floor_str = NULL;
	cub->data->ceil_str = NULL;
	check_texture_files(cub);
}

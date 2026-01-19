/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_rgb(int r, int g, int b)
{
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
		return (1);
	return (0);
}

uint32_t	parse_rgb(t_cub *cub, char *str)
{
	char	**part;
	int		r;
	int		g;
	int		b;

	if (!str)
		ft_exit(cub, "Error\nmissing color\n", INPUT_ERROR);
	part = ft_split(str, ',');
	if (!part || !part[0] || !part[1] || !part[2] || part[3])
	{
		if (part)
			ft_free_split_recursive(part, 0);
		ft_exit(cub, "Error\ninvalid color format\n", INPUT_ERROR);
	}
	r = ft_atoi(part[0]);
	g = ft_atoi(part[1]);
	b = ft_atoi(part[2]);
	if (!is_valid_rgb(r, g, b))
	{
		ft_free_split_recursive(part, 0);
		ft_exit(cub, "Error\ncolor values must be 0-255\n", INPUT_ERROR);
	}
	ft_free_split_recursive(part, 0);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

void	parse_texture(t_cub *cub, char **dest, char *line, int i)
{
	int		start;
	char	*tmp;

	if (line[i + 2] != ' ')
		ft_exit(cub, "Error\ninvalid texture path\n", PARSEING_TEXTURE_ERROR);
	i += 2;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		ft_exit(cub, "Error\nmissing texture path\n", PARSEING_TEXTURE_ERROR);
	start = i;
	while (line[i] && line[i] != ' ')
		i++;
	tmp = ft_substr(line, start, i - start);
	if (!tmp)
		ft_exit(cub, "Error\nmalloc failed\n", FAILD);
	if (*dest)
		free(*dest);
	*dest = tmp;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0')
		ft_exit(cub, "Error\ninvalid texture path\n", PARSEING_TEXTURE_ERROR);
}

void	parse_color(t_cub *cub, char **dest, char *line, int i)
{
	int	start;
	int	end;

	if (line[i + 1] != ' ')
		ft_exit(cub, "Error\ninvalid color format\n", PARSEING_TEXTURE_ERROR);
	i += 1;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		ft_exit(cub, "Error\nmissing color value\n", PARSEING_TEXTURE_ERROR);
	start = i;
	end = ft_strlen(line);
	while (end > start && (line[end - 1] == ' '))
		end--;
	*dest = ft_substr(line, start, end - start);
	if (!*dest)
		ft_exit(cub, "Error\ninvalid color values\n", FAILD);
}

int	set_texture(t_tex_set *a)
{
	if (*a->dst)
	{
		a->cub->error_message = ft_strdup(a->dup_err);
		return (0);
	}
	parse_texture(a->cub, a->dst, a->line, a->i);
	return (1);
}

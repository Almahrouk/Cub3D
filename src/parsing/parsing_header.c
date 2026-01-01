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

void	parse_texture(t_cub *cub, char **dest, char *line, int i)
{
	int	start;

	if (line[i + 2] != ' ' && line[i + 2] != '\t')
		ft_exit(cub, "Error\ninvalid texture path\n", PARSEING_TEXTURE_ERROR);
	i += 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		ft_exit(cub, "Error\nmissing texture path\n", PARSEING_TEXTURE_ERROR);
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	*dest = ft_substr(line, start, i - start);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\0')
		ft_exit(cub, "Error\ninvalid texture path\n", PARSEING_TEXTURE_ERROR);
}

void	parse_color(t_cub *cub, char **dest, char *line, int i)
{
	int	start;
	int	end;
	int	r;
	int	g;
	int	b;

	if (line[i + 1] != ' ' && line[i + 1] != '\t')
		ft_exit(cub, "Error\ninvalid color format\n", PARSEING_TEXTURE_ERROR);
	i += 1;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		ft_exit(cub, "Error\nmissing color value\n", PARSEING_TEXTURE_ERROR);
	start = i;
	end = ft_strlen(line);
	while (end > start && (line[end - 1] == ' ' || line[end - 1] == '\t'))
		end--;
	*dest = ft_substr(line, start, end - start);
	if (sscanf(*dest, "%d,%d,%d", &r, &g, &b) != 3
		|| r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_exit(cub, "Error\ninvalid color values\n", PARSEING_TEXTURE_ERROR);
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

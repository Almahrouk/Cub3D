/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeer42 <abeer42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2026/01/13 23:26:02 by abeer42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_texture_line(t_cub *cub, char *line, int i)
{
	t_tex_set	tex_set;

	if (ft_strncmp(&line[i], "NO", 2) == 0)
	{
		tex_set = (t_tex_set){cub, &cub->data->no, line, i,
			"Error\nduplicate NO\n"};
		return (set_texture(&tex_set));
	}
	if (ft_strncmp(&line[i], "SO", 2) == 0)
	{
		tex_set = (t_tex_set){cub, &cub->data->so, line, i,
			"Error\nduplicate SO\n"};
		return (set_texture(&tex_set));
	}
	if (ft_strncmp(&line[i], "WE", 2) == 0)
	{
		tex_set = (t_tex_set){cub, &cub->data->we, line, i,
			"Error\nduplicate WE\n"};
		return (set_texture(&tex_set));
	}
	if (ft_strncmp(&line[i], "EA", 2) == 0)
	{
		tex_set = (t_tex_set){cub, &cub->data->ea, line, i,
			"Error\nduplicate EA\n"};
		return (set_texture(&tex_set));
	}
	return (0);
}

int	parse_color_line(t_cub *cub, char *line, int i)
{
	if (line[i] == 'F')
	{
		if (cub->data->floor_str)
		{
			if (cub->error_message)
				free(cub->error_message);
			cub->error_message = ft_strdup("Error\nduplicate F\n");
			return (0);
		}
		parse_color(cub, &cub->data->floor_str, line, i);
	}
	else if (line[i] == 'C')
	{
		if (cub->data->ceil_str)
		{
			cub->error_message = ft_strdup("Error\nduplicate C\n");
			return (0);
		}
		parse_color(cub, &cub->data->ceil_str, line, i);
	}
	else
		return (0);
	return (1);
}

int	parse_header_line(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (1);
	if (ft_strncmp(&line[i], "NO", 2) == 0
		|| ft_strncmp(&line[i], "SO", 2) == 0
		|| ft_strncmp(&line[i], "WE", 2) == 0
		|| ft_strncmp(&line[i], "EA", 2) == 0)
		return (parse_texture_line(cub, line, i));
	else if (line[i] == 'F' || line[i] == 'C')
		return (parse_color_line(cub, line, i));
	else
		return (0);
}

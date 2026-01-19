/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 10:35:16 by aal-joul          #+#    #+#             */
/*   Updated: 2026-01-18 10:35:16 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*next_non_empty_line(t_cub *cub, char *line)
{
	while (1)
	{
		if (!line)
			line = get_next_line(cub->fd);
		if (!line)
		{
			map_error(cub, "Error\nmissing map\n");
		}
		strip_line_end(line);
		normalize_tabs(line);
		if (!is_line_empty(line))
			return (line);
		free(line);
		line = NULL;
	}
}

static void	parse_headers(t_cub *cub)
{
	char	*line;

	line = cub->line;
	cub->line = NULL;
	while (1)
	{
		line = next_non_empty_line(cub, line);
		if (is_map_line(line))
		{
			cub->line = line;
			return ;
		}
		if (!parse_header_line(cub, line))
		{
			if (!cub->error_message)
			{
				free(line);
				line = NULL;
				ft_exit(cub, "Error\ninvalid header line\n", MAP_ERROR);
			}
		}
		if (cub->error_message)
		{
			free(line);
			line = NULL;
			ft_exit(cub, cub->error_message, MAP_ERROR);
		}
		free(line);
		line = NULL;
	}
}

void	parsing(t_cub *cub)
{
	parse_headers(cub);
	parse_map(cub);
}

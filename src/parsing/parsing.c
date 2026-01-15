/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeer42 <abeer42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2026/01/13 22:23:59 by abeer42          ###   ########.fr       */
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
			map_error(cub, "Error\nmissing map\n");
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
				map_error(cub, "Error\ninvalid header line\n");
		}
		if (cub->error_message)
			map_error(cub, cub->error_message);
		free(line);
		line = NULL;
	}
}

void	parsing(t_cub *cub)
{
	parse_headers(cub);
	parse_map(cub);
}

/* end */

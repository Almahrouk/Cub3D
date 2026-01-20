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

static void	handle_header_line(t_cub *cub, char *line)
{
	if (!parse_header_line(cub, line))
	{
		if (!cub->error_message)
		{
			cub->current_line = NULL;
			free(line);
			ft_exit(cub, "Error\ninvalid header line\n", MAP_ERROR);
		}
	}
	if (cub->error_message)
	{
		cub->current_line = NULL;
		free(line);
		ft_exit(cub, cub->error_message, MAP_ERROR);
	}
}

static int	header_is_map_start(t_cub *cub, char *line)
{
	if (is_map_line(line))
	{
		cub->line = line;
		return (1);
	}
	return (0);
}

static void	parse_headers(t_cub *cub)
{
	char	*line;

	line = cub->line;
	cub->line = NULL;
	while (1)
	{
		cub->current_line = next_non_empty_line(cub, line);
		line = cub->current_line;
		if (header_is_map_start(cub, line))
		{
			cub->current_line = NULL;
			return ;
		}
		handle_header_line(cub, line);
		free(line);
		cub->current_line = NULL;
		line = NULL;
	}
}

void	parsing(t_cub *cub)
{
	parse_headers(cub);
	parse_map(cub);
}

// static void	parse_headers(t_cub *cub)
// {
// 	char	*line;

// 	line = cub->line;
// 	cub->line = NULL;
// 	while (1)
// 	{
// 		line = next_non_empty_line(cub, line);
// 		if (is_map_line(line))
// 		{
// 			cub->line = line;
// 			return ;
// 		}
// 		cub->line = line;
// 		if (!parse_header_line(cub, line))
// 		{
// 			if (!cub->error_message)
// 			{
// 				cub->line = NULL;
// 				free(line);
// 				line = NULL;
// 				ft_exit(cub, "Error\ninvalid header line\n", MAP_ERROR);
// 			}
// 		}
// 		if (cub->error_message)
// 		{
// 			cub->line = NULL;
// 			free(line);
// 			line = NULL;
// 			ft_exit(cub, cub->error_message, MAP_ERROR);
// 		}
// 		cub->line = NULL;
// 		free(line);
// 		line = NULL;
// 	}
// }

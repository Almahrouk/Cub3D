/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_map_filled(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->map_h)
	{
		x = 0;
		while (x < cub->map_w)
		{
			if (cub->map[y][x] == 'F')
			{
				if (is_invalid_neighbor(cub, x, y))
					ft_exit(cub, "Error\nmap is not closed\n", MAP_ERROR);
			}
			x++;
		}
		y++;
	}
}

void	validate_map(t_cub *cub)
{
	int	y;
	int	x;

	if (!cub->map || cub->map_h == 0 || cub->map_w == 0)
		map_error(cub, "Error\nempty map\n");
	check_map_content(cub);
	flood_fill(cub, cub->data->player_x, cub->data->player_y);
	check_map_filled(cub);
	y = 0;
	while (y < cub->map_h)
	{
		x = 0;
		while (x < cub->map_w)
		{
			if (cub->map[y][x] == 'F')
				cub->map[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	parse_map(t_cub *cub)
{
	t_map_parser	p;

	p.lines = NULL;
	p.line = cub->line;
	cub->line = NULL;
	p.map_started = false;
	p.map_ended = false;
	while (read_next_line(cub, &p))
		process_map_line(cub, &p);
	if (!p.lines)
		map_error(cub, "Error\nmissing map\n");
	build_map(cub, p.lines);
	ft_lstclear(&p.lines, free);
	validate_map(cub);
}

// void	parse_map(t_cub *cub)
// {
// 	char	*line;
// 	t_list	*lines;
// 	bool	map_started;
// 	bool	map_ended;

// 	lines = NULL;
// 	line = cub->line;
// 	cub->line = NULL;
// 	map_started = false;
// 	map_ended = false;
// 	while (1)
// 	{
// 		if (!line)
// 			line = get_next_line(cub->fd);
// 		if (!line)
// 			break ;
// 		strip_line_end(line);
// 		normalize_tabs(line);
// 		if (is_line_empty(line))
// 		{
// 			if (map_started)
// 				map_ended = true;
// 			free(line);
// 			line = NULL;
// 			continue ;
// 		}
// 		if (map_ended)
// 		{
// 			free(line);
// 			ft_lstclear(&lines, free);
// 			ft_exit(cub, "Error\nmap invalid\n", MAP_ERROR);
// 		}
// 		map_started = true;
// 		ft_lstadd_back(&lines, ft_lstnew(line));
// 		line = NULL;
// 	}
// 	if (!lines)
// 		map_error(cub, "Error\nmissing map\n");
// 	build_map(cub, lines);
// 	ft_lstclear(&lines, free);
// 	validate_map(cub);
// }

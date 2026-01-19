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

void	handle_player_tile(t_cub *cub, int x, int y, int *player_count)
{
	(*player_count)++;
	cub->data->player_x = x;
	cub->data->player_y = y;
	cub->player_dir = cub->map[y][x];
	cub->data->pov = cub->map[y][x];
	cub->map[y][x] = '0';
}

void	check_map_tile(t_cub *cub, int x, int y, int *player_count)
{
	char	c;

	c = cub->map[y][x];
	if (!is_map_char(c))
		map_error(cub, "Error\ninvalid map character\n");
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		handle_player_tile(cub, x, y, player_count);
}

void	check_map_content(t_cub *cub)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < cub->map_h)
	{
		x = 0;
		while (x < cub->map_w)
		{
			check_map_tile(cub, x, y, &player_count);
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		map_error(cub, "Error\ninvalid player count\n");
	}
}

void	validate_map(t_cub *cub)
{
	int	x;
	int	y;

	if (!cub->map || cub->map_h == 0 || cub->map_w == 0)
		map_error(cub, "Error\nempty map\n");
	check_map_content(cub);
	x = 0;
	while (x < cub->map_w)
	{
		if (cub->map[0][x] == '0' || cub->map[cub->map_h - 1][x] == '0')
			ft_exit(cub, "Error\nmap is not closed\n", MAP_ERROR);
		x++;
	}
	y = 0;
	while (y < cub->map_h)
	{
		if (cub->map[y][0] == '0' || cub->map[y][cub->map_w - 1] == '0')
			ft_exit(cub, "Error\nmap is not closed\n", MAP_ERROR);
		y++;
	}
	flood_fill(cub, cub->data->player_x, cub->data->player_y);
}

void	parse_map(t_cub *cub)
{
	char	*line;
	t_list	*lines;
	int		map_started;

	lines = NULL;
	line = cub->line;
	map_started = 0;
	cub->line = NULL;
	while (line)
	{
		strip_line_end(line);
		normalize_tabs(line);
		if (is_line_empty(line))
		{
			if (map_started)
			{
				free(line);
				ft_exit(cub, "Error\nmap duplicate\n", MAP_ERROR);
			}
			free(line);
			line = get_next_line(cub->fd);
			continue ;
		}
		if (!map_started)
			map_started = 1;
		ft_lstadd_back(&lines, ft_lstnew(line));
		line = get_next_line(cub->fd);
	}
	build_map(cub, lines);
	validate_map(cub);
}

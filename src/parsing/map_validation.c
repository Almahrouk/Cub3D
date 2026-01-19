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

static void	check_map_filled(t_cub *cub)
{
	int	x;
	int	y;

	for (y = 0; y < cub->map_h; y++)
	{
		for (x = 0; x < cub->map_w; x++)
		{
			if (cub->map[y][x] == '0')
			{
				if (x == 0 || y == 0 || x == cub->map_w - 1
					|| y == cub->map_h - 1
					|| cub->map[y][x - 1] == ' '
					|| cub->map[y][x + 1] == ' '
					|| cub->map[y - 1][x] == ' '
					|| cub->map[y + 1][x] == ' ')
				{
					ft_exit(cub, "Error\nmap is not closed\n", MAP_ERROR);
				}
			}
		}
	}
}

void	validate_map(t_cub *cub)
{
	if (!cub->map || cub->map_h == 0 || cub->map_w == 0)
		map_error(cub, "Error\nempty map\n");
	check_map_content(cub);
	flood_fill(cub, cub->data->player_x, cub->data->player_y);
	check_map_filled(cub);
	for (int y = 0; y < cub->map_h; y++)
		for (int x = 0; x < cub->map_w; x++)
			if (cub->map[y][x] == 'F')
				cub->map[y][x] = '0';
}

void	parse_map(t_cub *cub)
{
	char	*line;
	t_list	*lines;
	bool	map_started;
	bool	map_ended;

	lines = NULL;
	line = cub->line;
	cub->line = NULL;
	map_started = false;
	map_ended = false;
	while (line || (line = get_next_line(cub->fd)))
	{
		strip_line_end(line);
		normalize_tabs(line);
		if (is_line_empty(line))
		{
			if (map_started)
				map_ended = true;
			free(line);
			line = NULL;
			continue ;
		}
		if (map_ended)
		{
			free(line);
			ft_lstclear(&lines, free);
			ft_exit(cub, "Error\nmap invalid\n", MAP_ERROR);
		}
		map_started = true;
		ft_lstadd_back(&lines, ft_lstnew(line));
		line = NULL;
	}
	if (!lines)
		map_error(cub, "Error\nmissing map\n");
	build_map(cub, lines);
	ft_lstclear(&lines, free);
	validate_map(cub);
}

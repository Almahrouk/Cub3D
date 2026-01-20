/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	map_error(t_cub *cub, char *message)
{
	ft_exit(cub, message, MAP_ERROR);
}

void	handle_empty_line(t_map_parser *p)
{
	if (p->map_started)
		p->map_ended = true;
	free(p->line);
	p->line = NULL;
}

void	map_invalid_exit(t_cub *cub, t_map_parser *p)
{
	free(p->line);
	ft_lstclear(&p->lines, free);
	ft_exit(cub, "Error\nmap invalid\n", MAP_ERROR);
}

void	process_map_line(t_cub *cub, t_map_parser *p)
{
	strip_line_end(p->line);
	normalize_tabs(p->line);
	if (is_line_empty(p->line))
	{
		handle_empty_line(p);
		return ;
	}
	if (p->map_ended)
		map_invalid_exit(cub, p);
	p->map_started = true;
	ft_lstadd_back(&p->lines, ft_lstnew(p->line));
	p->line = NULL;
}

bool	read_next_line(t_cub *cub, t_map_parser *p)
{
	if (!p->line)
		p->line = get_next_line(cub->fd);
	return (p->line != NULL);
}

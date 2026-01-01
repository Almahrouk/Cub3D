/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr     #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ff_init(t_cub *cub, t_ff *ff, int start_x, int start_y)
{
	ff->w = cub->map_w;
	ff->h = cub->map_h;
	ff->max = ff->w * ff->h;
	ff->stack_x = malloc(sizeof(int) * (ff->max + 1));
	ff->stack_y = malloc(sizeof(int) * (ff->max + 1));
	ff->visited = ft_calloc(ff->max, sizeof(char));
	if (!ff->stack_x || !ff->stack_y || !ff->visited)
		map_error(cub, "Error\nmemory allocation failed\n");
	ff->top = 0;
	ff->stack_x[ff->top] = start_x;
	ff->stack_y[ff->top] = start_y;
	ff->top++;
}

static void	ff_push(t_ff *ff, int x, int y)
{
	ff->stack_x[ff->top] = x;
	ff->stack_y[ff->top] = y;
	ff->top++;
}

static void	ff_check_cell(t_cub *cub, t_ff *ff)
{
	if (ff->x < 0 || ff->y < 0 || ff->x >= ff->w || ff->y >= ff->h)
		map_error(cub, "Error\nmap is not closed\n");
	ff->idx = ff->y * ff->w + ff->x;
	if (ff->visited[ff->idx])
		return ;
	if (cub->map[ff->y][ff->x] == ' ')
		map_error(cub, "Error\nmap is not closed\n");
	if (cub->map[ff->y][ff->x] == '1')
		return ;
	ff->visited[ff->idx] = 1;
}

static void	ff_expand(t_ff *ff)
{
	if (ff->x > 0 && !ff->visited[ff->idx - 1])
		ff_push(ff, ff->x - 1, ff->y);
	if (ff->x < ff->w - 1 && !ff->visited[ff->idx + 1])
		ff_push(ff, ff->x + 1, ff->y);
	if (ff->y > 0 && !ff->visited[ff->idx - ff->w])
		ff_push(ff, ff->x, ff->y - 1);
	if (ff->y < ff->h - 1 && !ff->visited[ff->idx + ff->w])
		ff_push(ff, ff->x, ff->y + 1);
}

void	flood_fill(t_cub *cub, int start_x, int start_y)
{
	t_ff	ff;

	ff_init(cub, &ff, start_x, start_y);
	while (ff.top > 0)
	{
		ff.x = ff.stack_x[--ff.top];
		ff.y = ff.stack_y[ff.top];
		ff_check_cell(cub, &ff);
		if (!ff.visited[ff.idx])
			continue ;
		ff_expand(&ff);
	}
	ff_free(&ff);
}

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

static void	try_push(t_ff *ff, int x, int y)
{
	int	idx;

	if (x < 0 || y < 0 || x >= ff->w || y >= ff->h)
		return ;
	idx = y * ff->w + x;
	if (ff->visited[idx])
		return ;
	ff->visited[idx] = 1;
	ff->stack_x[ff->top] = x;
	ff->stack_y[ff->top] = y;
	ff->top++;
}

static void	ff_expand(t_ff *ff)
{
	int	x;
	int	y;

	x = ff->x;
	y = ff->y;
	try_push(ff, x - 1, y);
	try_push(ff, x + 1, y);
	try_push(ff, x, y - 1);
	try_push(ff, x, y + 1);
	try_push(ff, x - 1, y - 1);
	try_push(ff, x + 1, y - 1);
	try_push(ff, x - 1, y + 1);
	try_push(ff, x + 1, y + 1);
}

void	flood_fill(t_cub *cub, int start_x, int start_y)
{
	t_ff	ff;

	ff_init(cub, &ff, start_x, start_y);
	while (ff.top > 0)
	{
		ff.x = ff.stack_x[--ff.top];
		ff.y = ff.stack_y[ff.top];
		if (ff.x < 0 || ff.y < 0
			|| ff.x >= ff.w || ff.y >= ff.h)
		{
			ff_free(&ff);
			ft_exit(cub, "Error\nmap is not closed\n", MAP_ERROR);
		}
		if (cub->map[ff.y][ff.x] == ' ')
		{
			ff_free(&ff);
			ft_exit(cub, "Error\nmap is not closed\n", MAP_ERROR);
		}
		if (cub->map[ff.y][ff.x] == '1')
			continue ;
		if (cub->map[ff.y][ff.x] == '0')
			cub->map[ff.y][ff.x] = 'F';
		ff_expand(&ff);
	}
	ff_free(&ff);
}

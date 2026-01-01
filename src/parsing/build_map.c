/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_max_width(t_list *lines)
{
	t_list	*tmp;
	int		max_w;
	int		len;

	tmp = lines;
	max_w = 0;
	while (tmp)
	{
		len = ft_strlen((char *)tmp->content);
		if (len > max_w)
			max_w = len;
		tmp = tmp->next;
	}
	return (max_w);
}

static void	alloc_map_array(t_cub *cub, t_list *lines)
{
	if (!lines)
    {
        printf("No lines provided to build the map.\n"); // Debug line
		map_error(cub, "Error\nmissing map\n");
    }
	cub->map_h = ft_lstsize(lines);
	cub->map_w = get_max_width(lines);
	cub->map = malloc(sizeof(char *) * (cub->map_h + 1));
	if (!cub->map)
		map_error(cub, "Error\nmemory allocation failed\n");
}

static char	*build_row(t_cub *cub, char *src)
{
	int		len;
	char	*row;

	len = ft_strlen(src);
	row = malloc(sizeof(char) * (cub->map_w + 1));
	if (!row)
		map_error(cub, "Error\nmemory allocation failed\n");
	ft_memset(row, ' ', cub->map_w);
	ft_memcpy(row, src, len);
	row[cub->map_w] = '\0';
	return (row);
}

static void	fill_map_rows(t_cub *cub, t_list *lines)
{
	int		i;
	t_list	*node;

	i = 0;
	node = lines;
	while (node)
	{
		cub->map[i++] = build_row(cub, (char *)node->content);
		node = node->next;
	}
	cub->map[i] = NULL;
}

void	build_map(t_cub *cub, t_list *lines)
{
	alloc_map_array(cub, lines);
	fill_map_rows(cub, lines);
	ft_lstclear(&lines, free);
}

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

void	ff_free(t_ff *ff)
{
	if (!ff)
		return ;
	free(ff->stack_x);
	free(ff->stack_y);
	free(ff->visited);
	ff->stack_x = NULL;
	ff->stack_y = NULL;
	ff->visited = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_exit(t_cub *cub, char *message, int err_no)
{
	if (cub && cub->test_mode)
	{
		if (cub->error_message)
			free(cub->error_message);
		cub->error_message = ft_strdup(message);
		cub->error_code = err_no;
		return ;
	}
	if (message)
		write(2, message, ft_strlen(message));
	if (cub && cub->error_message)
	{
		free(cub->error_message);
		cub->error_message = NULL;
	}
	get_next_line_cleanup();
	free_memory(cub);
	exit(err_no);
}

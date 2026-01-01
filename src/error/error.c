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
		cub->error_message = ft_strdup(message);
		cub->error_code = err_no;
		return ;
	}
	perror(message);
	exit(err_no);
}

void	ft_exit_input(char *message, int err_no)
{
	write(1, message, ft_strlen(message));
	exit(err_no);
}

void	print_bad(char *path, char *msg)
{
	printf("BAD %s: %s", path, msg);
	exit(1);
}

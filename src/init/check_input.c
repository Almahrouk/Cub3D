/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_file(t_cub *cub)
{
	cub->fd = open(cub->file_name, O_RDONLY);
	if (cub->fd == -1)
		ft_exit(cub, "Error\nopening file\n", OPEN_FILE_ERROR);
	cub->line = get_next_line(cub->fd);
	if (!cub->line)
		ft_exit(cub, "Error\nempty file\n", EMPTY_FILE_ERROR);
}

void	check_input(int ac, char **av, t_cub *cub)
{
	if (ac != 2)
		ft_exit_input("Error\nwrong number of arguments\n", INPUT_ERROR);
	else if (ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".cub", 5) != 0)
		ft_exit_input("Error\nfile must be .cub\n", INPUT_ERROR);
	cub->file_name = av[1];
}

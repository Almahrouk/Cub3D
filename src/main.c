/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	run_parse_checks(t_cub *cub, char *path)
{
	check_file(cub);
	if (cub->error_message)
		print_bad(path, cub->error_message);
	parsing(cub);
	if (cub->error_message)
		print_bad(path, cub->error_message);
	parse_map(cub);
	if (cub->error_message)
		print_bad(path, cub->error_message);
	check_textures(cub);
	if (cub->error_message)
		print_bad(path, cub->error_message);
}

void	test_map_child(char *path)
{
	t_cub	cub;

	init(&cub);
	cub.test_mode = 1;
	cub.file_name = ft_strdup(path);
	run_parse_checks(&cub, path);
	printf("GOOD %s\n", path);
	exit(0);
}

void	test_map(char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		test_map_child(path);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		printf("BAD %s: Segmentation fault\n", path);
}

int	init_game(t_cub *game)
{
	game->mlx = mlx_init(WIN_W, WIN_H, "cub3D", true);
	if (!game->mlx)
		return (EXIT_FAILURE);
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		return (EXIT_FAILURE);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	init_cub(ac, av, &cub);
	parsing(&cub);
	// parse_map(&cub);
	check_textures(&cub);
	init_game(&cub);
	return (EXIT_SUCCESS);
}

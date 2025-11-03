#include "cub3D.h"

int main(int ac, char **av)
{
	 t_cub cub;
	 t_game	game;

	init_cub(ac, av, &cub);
	parsing(&cub);
	parse_map(&cub);
	//check_textures(&cub);
	
	game.cub = &cub;
	game.mlx = mlx_init(800, 600, "cub3D", true);
	if (!game.mlx)
		return (EXIT_FAILURE);
	game.img = mlx_new_image(game.mlx, 800, 600);
	mlx_image_to_window(game.mlx, game.img, 0 ,0);
	draw_map(&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}

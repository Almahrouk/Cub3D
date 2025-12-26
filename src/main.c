#include "cub3D.h"

int	init_game(t_cub *game)
{
	game->mlx = mlx_init(WIN_W, WIN_H, "cub3D", true);
	if (!game->mlx)
		return (EXIT_FAILURE);
		//handle_error("Error: mlx_init failed.");
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
		return (EXIT_FAILURE);
		//handle_error("Error open window.\n");
	if(mlx_image_to_window(game->mlx, game->img, 0 ,0) < 0)
		return (EXIT_FAILURE);
		//handle_error("Error mlx_image_to_window.\n");
	//draw_map(game);
	/*setup(game);
	mlx_key_hook(game->mlx, hook_key_press, game);
	mlx_loop_hook(game->mlx, draw_playerview, game);
	mlx_close_hook(game->mlx, hook_close, game);
	*/
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	 t_cub cub;

	init_cub(ac, av, &cub);
	parsing(&cub);
	parse_map(&cub);
	//check_textures(&cub);
	
	init_game(&cub);
	return (EXIT_SUCCESS);
}

#include "cub3D.h"

int main(int ac, char **av)
{
	// t_cub cub;

	// init_cub(ac, av, &cub);
	// parsing(&cub);
	// check_textures(&cub);
	(void)ac;
	(void)av;
	mlx_t *mlx = mlx_init(800, 600, "cub3D", true);
	if (!mlx)
		return (EXIT_FAILURE);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

#include "cub3D.h"

int main(int ac, char **av)
{
    t_cub cub;

    init_cub(ac, av, &cub);
    parsing(&cub);
    check_textures(&cub);
	return (EXIT_SUCCESS);
}
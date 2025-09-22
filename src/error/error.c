#include "cub3D.h"

void ft_exit(t_cub *cub)
{
    free(cub->map);
    exit(EXIT_FAILURE);
}
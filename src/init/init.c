#include "cub3D.h"

void init_map(t_map *map)
{
    map->i = 0;
}

void init(t_cub *cub)
{
    cub->fd = -1;
    cub->map = malloc(sizeof(t_map));
    if (!cub->map)
    {
        perror("Error allocating map");
        exit(EXIT_FAILURE);
    }
    init_map(cub->map);
}

void init_cub(int ac, char **av, t_cub *cub)
{
    init(cub);
    check_input(ac);
    check_file(ac, av, cub);
}
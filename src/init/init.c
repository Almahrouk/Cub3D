#include "cub3D.h"

void init(t_cub *cub)
{
    cub->fd = -1;
    cub->line = NULL;
    cub->file_name = NULL;
    cub->north_path = NULL;
    cub->south_path = NULL;
    cub->west_path = NULL;
    cub->east_path = NULL;
    cub->floor_color = NULL;
    cub->ceiling_color = NULL;
    cub->map = NULL;
    cub->map_w = 0;
    cub->map_h = 0;
    cub->player_x = -1;
    cub->player_y = -1;
    cub->player_dir = '\0';
    
}

void init_cub(int ac, char **av, t_cub *cub)
{
    init(cub);
    check_input(ac, av, cub);
    check_file(cub);
}

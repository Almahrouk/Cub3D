#include "cub3D.h"

t_vector    creat_vector(double x, double y)
{
    t_vector    v;

    v.x = x;
    v.y = y;
    return (v);
}

void    setup(t_cub *game)
{
    game->pos = creat_vector(game->data->player_x + 0.5, game->data->player_y + 0.5);
    //
}
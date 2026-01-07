#include "cub3D.h"

t_vector    creat_vector(double x, double y)
{
    t_vector    v;

    v.x = x;
    v.y = y;
    return (v);
}

static void define_plane(t_cub *game)
{
    if (game->data->pov_player == 'N')
    {
        game->dir = creat_vector(0, -1);
        game->cam_plane = creat_vector(0.66, 0);
    }
    else if (game->data->pov_player == 'S')
    {
        game->dir = creat_vector(0, 1);
        game->cam_plane = creat_vector(-0.66, 0);
    }
    else if (game->data->pov_player == 'W')
    {
        game->dir = creat_vector(-1, 0);
        game->cam_plane = creat_vector(0, -0.66);
    }
    else if (game->data->pov_player == 'E')
    {
        game->dir = creat_vector(1, 0);
        game->cam_plane = creat_vector(0, 0.66);
    }
}

void    setup(t_cub *game)
{
    game->pos = creat_vector(game->data->player_x + 0.5, game->data->player_y + 0.5);
    define_plane(game);
}
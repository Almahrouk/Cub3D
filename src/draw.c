#include "cub3D.h"

void    draw_square(t_game *game, int x, int y, uint23_t color)
{
    int i;
    int j;

    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            mlx_put_pixel(game->img, x + j, y + i, color)
        }
        i++;
    }
}

void    draw_map(t_game *game)
{
    int     y;
    int     x;
    char    **map = game->cub->map;
    
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                draw_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x808080FF)
            else
                draw_square(game, x * TILE_SIZE, y * TILE_SIZE, 0xFFFFFFFF)
            x++;
        }
        y++;
    }
    draw_square(game, (int)(game->cub->player_x * TILE_SIZE),
                (int)(game->cub->player_y * TILE_SIZE),
                 0xFF0000FF);

}

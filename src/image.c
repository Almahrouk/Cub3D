#include "cub3D.h"

void    load_tex(t_cub *game)
{
    game->north = init_tex(game->data->no);
    game->south = init_textures(game->data->so);
	game->west = init_textures(game->data->we);
	game->east = init_textures(game->data->ea);
}

mlx_texture_t   *init_tex(char  *path)
{
    mlx_texture_t   *img;

    img = mlx_load_png(path);
    if (!img)
        return (EXIT_FAILURE);
        //handle_error("Error: mlx_load_png failed");
        return (img);
}
#include "cub3D.h"

static void free_map(t_cub *cub)
{
    int i;

    if (!cub || !cub->map)
        return;
    for (i = 0; i < cub->map_h; i++)
        free(cub->map[i]);
    free(cub->map);
    cub->map = NULL;
}

static void free_data(t_cub *cub)
{
    if (!cub || !cub->data)
        return;
    free(cub->data->no);
    free(cub->data->so);
    free(cub->data->we);
    free(cub->data->ea);
    free(cub->data->floor_str);
    free(cub->data->ceil_str);
    free(cub->data);
    cub->data = NULL;
}

static void free_textures(t_cub *cub)
{
    if (!cub)
        return;
    if (cub->north_t) mlx_delete_texture(cub->north_t);
    if (cub->south_t) mlx_delete_texture(cub->south_t);
    if (cub->west_t)  mlx_delete_texture(cub->west_t);
    if (cub->east_t)  mlx_delete_texture(cub->east_t);
    cub->north_t = NULL;
    cub->south_t = NULL;
    cub->west_t = NULL;
    cub->east_t = NULL;
}

static void free_mlx(t_cub *cub)
{
    if (!cub)
        return;
    if (cub->img) mlx_delete_image(cub->mlx, cub->img);
    cub->img = NULL;
    if (cub->mlx)
        mlx_terminate(cub->mlx);
    cub->mlx = NULL;
}

void free_memory(t_cub *cub)
{
    if (!cub)
        return;
    free_map(cub);
    free_data(cub);
    free_textures(cub);
    free_mlx(cub);
}

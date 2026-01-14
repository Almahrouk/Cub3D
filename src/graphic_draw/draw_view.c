#include "cub3D.h"

void    process_result(t_cub *game)
{
    float   new_x;
    float   new_y;

    calculate_new_pos(game, &new_x, &new_y);
    if (can_move_to(game, new_x, new_y))
    {
        game->pos.x = new_x;
        game->pos.y = new_y;
    }
    if (game->keys.l)
    {
        game->dir = rotate_vector(game->dir , -1.5);
        game->camera_plane = rotate_vector(game->camera_plane, -1.5);
    }
    if (game->keys.r)
    {
        game->dir = rotate_vector(game->dir , 1.5);
        game->camera_plane = rotate_vector(game->camera_plane, 1.5);
    }
}

void    draw_background(t_cub *game)
{
    uint32_t    x;
    uint32_t    y;

    y = 0;
    while (y < game->img->height / 2)
    {
        x = 0;
        while (x < game->img->width)
        {
            mlx_put_pixel(game->img, x, y, game->data->ceil);
            x++;
        }
        y++;
    }
    while (y < game->img->height)
    {
        x = 0;
        while (x < game->img->width)
        {
            mlx_put_pixel(game->img, x, y, game->data->floor);
            x++;
        }
        y++;
    }
}

void    update_fps(t_cub *game)
{
    char                *fps_n;
    char                *fps_txt;
    static int           fps_len;
    static mlx_image_t  *fps_img;

    //fps_len++;
    if (fps_len % 15 == 0)
    {
        game->frame = game->mlx->delta_time;
        if (fps_img)
            mlx_delete_image(game->mlx, fps_img);
        fps_n = ft_itoa(1 / game->mlx->delta_time);
        fps_txt = ft_strjoin("FPS: ", fps_n);
        free(fps_n);
        fps_img = mlx_put_string(game->mlx, fps_txt,
            WIN_W - 80, WIN_H - 590);
        free(fps_txt);
    }
}

void    send_rays(t_cub *game)
{
    int     pixel;
    t_dda   ray;

    pixel = 0;
    while (pixel < WIN_W)
    {
        ray.plane_mult = 2 * pixel / (float)WIN_W - 1;
        ray.camera_pix = mult_vector(game->camera_plane,
                ray.plane_mult);
        ray.dir = add_vector(game->dir, ray.camera_pix);
        ray.step.x = set_dir(ray.dir.x);
        ray.step.y = set_dir(ray.dir.y);
        calculate_delta_dist(&ray);
        calculate_dist_2side(game, &ray);
        dda_algo(game, &ray);
        draw_wall(game, &ray, pixel);
        pixel++;
    }
}

void    draw_view(void *p)
{
    t_cub   *game;

    game = (t_cub *)p;
    process_result(game);
    draw_background(game);
    update_fps(game);
    send_rays(game);
}
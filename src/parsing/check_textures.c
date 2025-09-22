#include "cub3D.h"

void check_textures_paths(t_cub *cub, char *path, char *message)
{
    if (ft_strncmp(path + ft_strlen(path) -4,
                   ".xpm", 5) != 0)
        ft_exit(cub, message, TEXTURE_PATH_ERROR);
}

void check_textures_open(t_cub *cub, char *path, char *message)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        ft_exit(cub, message, TEXTURE_OPEN_ERROR);
    close(fd);
}

void check_textures(t_cub *cub)
{
    if (!cub->north_path || !cub->south_path
        || !cub->west_path || !cub->east_path)
        ft_exit(cub, "Error\nmissing texture path(s)\n", MISSING_TEXTURE_ERROR);
    check_textures_paths(cub, cub->north_path, "Error\nnorth texture must be .xpm\n");
    check_textures_paths(cub, cub->south_path, "Error\nsouth texture must be .xpm\n");
    check_textures_paths(cub, cub->west_path, "Error\nwest texture must be .xpm\n");
    check_textures_paths(cub, cub->east_path, "Error\neast texture must be .xpm\n");
    check_textures_open(cub, cub->north_path, "Error\nopening north texture\n");
    check_textures_open(cub, cub->south_path, "Error\nopening south texture\n");
    check_textures_open(cub, cub->west_path, "Error\nopening west texture\n");
    check_textures_open(cub, cub->east_path, "Error\nopening east texture\n");
    printf("All textures are valid and accessible.\n");
}
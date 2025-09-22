#include "cub3D.h"

void ft_exit(t_cub *cub, char *message, int errno)
{
    (void)cub;
    perror(message);
    exit(errno);
}

void ft_exit_input(char *message, int errno)
{
    write(1, message, ft_strlen(message));
    exit(errno);
}
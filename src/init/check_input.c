#include "cub3D.h"

void check_file(int ac, char **av, t_cub *cub)
{
    (void)ac;
    (void)av;
    cub->fd = open(av[1], O_RDONLY);

    if (cub->fd == -1)
    {
        perror("Error\nopening file\n");
        ft_exit(cub);
    }
    printf("File is open\n");
    close(cub->fd);
}

void check_input(int ac)
{
    if(ac != 2)
    {
        write(1, "ERROR\n", 7);
        exit(EXIT_FAILURE);
    }
}

/*
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("example.cub", O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        return (1);
    }

    // File opened successfully
    printf("File opened successfully! File descriptor: %d\n", fd);

    close(fd);
    return 0;
}

*/
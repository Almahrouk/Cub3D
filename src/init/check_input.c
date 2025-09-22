#include "cub3D.h"

// check memory leak
void check_file(t_cub *cub)
{
    cub->fd = open(cub->file_name, O_RDONLY);
    if (cub->fd == -1)
        ft_exit(cub, "Error\nopening file\n", OPEN_FILE_ERROR);
    cub->line = get_next_line(cub->fd);
    if (!cub->line)
        ft_exit(cub, "Error\nempty file\n", EMPTY_FILE_ERROR);
    // close(cub->fd);
}

void check_input(int ac, char **av, t_cub *cub)
{
    if (ac != 2)
        ft_exit_input("Error\nwrong number of arguments\n", INPUT_ERROR);
    else if (ft_strncmp(&av[1][ft_strlen(av[1]) -4], ".cub", 5) != 0)
        ft_exit_input("Error\nfile must be .cub\n", INPUT_ERROR);
    cub->file_name = av[1];
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
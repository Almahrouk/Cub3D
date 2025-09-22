#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h> // strerror
// # include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
// # include <signal.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// # include <stddef.h>
# include <sys/time.h> // gettimeofday
# include <math.h>


# include "../libft/libft.h"

typedef enum e_error
{
	SUCCESS,
	FAILD,
	FILE_ERROR,
}	t_error;

typedef struct s_map
{
    int i;
}	t_map;

typedef struct s_cub
{
    int fd;
	t_map *map;
}	t_cub;

void init_cub(int ac, char **av, t_cub *cub);
void init_map(t_map *map);
void init(t_cub *cub);

void check_input(int ac);
void check_file(int ac, char **av, t_cub *cub);

void ft_exit(t_cub *cub);



#endif
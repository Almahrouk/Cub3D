#ifndef CUB3D_H
# define CUB3D_H


# include <string.h> // strerror
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h> // gettimeofday
# include <math.h>

# include "../libft/libft.h"

// use echo $?
typedef enum e_error
{
	SUCCESS,
	FAILD,
	INPUT_ERROR,    
	OPEN_FILE_ERROR, 
	EMPTY_FILE_ERROR,
	PARSEING_TEXTURE_ERROR,
	MISSING_TEXTURE_ERROR,
	TEXTURE_PATH_ERROR,
	TEXTURE_OPEN_ERROR
}	t_error;

typedef struct s_cub
{
    int fd;
	char *line;
	char *file_name;
	char *north_path;
	char *south_path;
	char *west_path;
	char *east_path;
}	t_cub;

void init(t_cub *cub);
void init_cub(int ac, char **av, t_cub *cub);

void check_file(t_cub *cub);
void check_input(int ac, char **av, t_cub *map);

void ft_exit(t_cub *cub, char *message, int errno);
void ft_exit_input(char *message, int errno);

void parsing(t_cub *cub);
void check_textures(t_cub *cub);




#endif
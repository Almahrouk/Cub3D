#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <math.h>
# include <string.h> // strerror
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h> // gettimeofday
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define MINIMAP_W	100
# define MINIMAP_H	100
# define WIN_W		1000
# define WIN_H		800
# define TILE_SIZE	64
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
	TEXTURE_OPEN_ERROR,
	MAP_ERROR
}	t_error;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_data
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			**map;
	/*t_cub			*cub;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;*/
	//char	**map;
	//t_player	p;
	int		player_x;
	int		player_y;
}	t_data;

typedef struct s_cub
{
	int		fd;
	char	*line;
	char	*file_name;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	char	*floor_color;
	char	*ceiling_color;
	char	**map;
	int		map_w;
	int		map_h;
	int		player_x;
	int		player_y;
	char	player_dir;
	mlx_t	*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	t_vector		pos;
	t_data	*data;
}	t_cub;

// typedef struct s_player
// {
// 	double	x;
// 	double	y;
// 	double	dir_x;
// 	double	dir_y;
// 	double	plane_x;
// 	double	plane_y;
// } t_player;

void	init(t_cub *cub);
void	init_cub(int ac, char **av, t_cub *cub);

void	check_file(t_cub *cub);
void	check_input(int ac, char **av, t_cub *map);

void	ft_exit(t_cub *cub, char *message, int errno);
void	ft_exit_input(char *message, int errno);

void	parsing(t_cub *cub);
void	check_textures(t_cub *cub);

void	parse_map(t_cub *cub);
//void	draw_map(t_game *game);

#endif

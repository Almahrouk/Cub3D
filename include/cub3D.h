/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almah <almah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by almah             #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by almah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <math.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <sys/wait.h>

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
	int				player_x;
	int				player_y;
}	t_data;

typedef struct s_cub
{
	int				fd;
	char			*line;
	char			*file_name;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	char			*floor_color;
	char			*ceiling_color;
	char			**map;
	int				map_w;
	int				map_h;
	int				player_x;
	int				player_y;
	char			player_dir;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	t_vector		pos;
	t_data			*data;
	int				test_mode;
	int				error_code;
	char			*error_message;
}	t_cub;

typedef struct s_ff
{
	int		w;
	int		h;
	int		max;
	int		top;
	int		x;
	int		y;
	int		idx;
	int		*stack_x;
	int		*stack_y;
	char	*visited;
}	t_ff;

typedef struct s_tex_set
{
	t_cub	*cub;
	char	**dst;
	char	*line;
	int		i;
	char	*dup_err;
}	t_tex_set;

int	init_game(t_cub *game);
void	run_parse_checks(t_cub *cub, char *path);
void	test_map_child(char *path);
void	test_map(char *path);

void	init(t_cub *cub);
void	init_cub(int ac, char **av, t_cub *cub);
void	print_bad(char *path, char *msg);

void	check_file(t_cub *cub);
void	check_input(int ac, char **av, t_cub *map);

void	ft_exit(t_cub *cub, char *message, int errno);
void	ft_exit_input(char *message, int errno);

void	parsing(t_cub *cub);
void	check_textures(t_cub *cub);

void	parse_map(t_cub *cub);
//void	draw_map(t_game *game);
void	map_error(t_cub *cub, char *message);
void	strip_line_end(char *line);
void	normalize_tabs(char *line);
int		is_line_empty(char *line);
int		is_map_char(char c);
void	flood_fill(t_cub *cub, int start_x, int start_y);
void	build_map(t_cub *cub, t_list *lines);
void	handle_player_tile(t_cub *cub, int x, int y, int *player_count);
void	check_map_tile(t_cub *cub, int x, int y, int *player_count);
void	check_map_content(t_cub *cub);
void	check_textures_open(t_cub *cub, char *path, char *msg);

void	validate_map(t_cub *cub);
int		is_map_line(char *line);
int		parse_header_line(t_cub *cub, char *line);
void	ff_free(t_ff *ff);
void	parse_texture(t_cub *cub, char **dest, char *line, int i);
void	parse_color(t_cub *cub, char **dest, char *line, int i);
int	set_texture(t_tex_set *a);
int	parse_texture_line(t_cub *cub, char *line, int i);
int	parse_color_line(t_cub *cub, char *line, int i);
int	parse_header_line(t_cub *cub, char *line);




#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeer42 <abeer42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by almah             #+#    #+#             */
/*   Updated: 2026/01/16 17:38:03 by abeer42          ###   ########.fr       */
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
# define PI 3.141592653589793

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

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_dda
{
	int			hit_side;
	float		perp_dist;
	float		wall_hit;
	float		plane_mult;
	t_vector	dir;
	t_vector	camera_pix;
	t_vector	delta_dist;
	t_vector	dist_side;
	t_coord		map;
	t_coord		step;	
}	t_dda;


typedef struct s_data
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			**map;
	char			pov;
	int				player_x;
	int				player_y;
	char			*ceil_str;
	char			*floor_str;
	uint32_t		floor;
	uint32_t		ceil;
}	t_data;

typedef struct s_key
{
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	l;
	bool	r;

}	t_key;

typedef struct s_wall
{
	int		h;
	int		start_y;
	int		end_y;
	int		tex_x;
	int		tex_y;
	float	point_x;
	float	tex_step;
	float	tex_pos;	
}	t_wall;

typedef struct s_cub
{
	int				fd;
	int				map_w;
	int				map_h;
	int				hit_side;
	int				test_mode;
	int				error_code;
	char			player_dir;
	char			*line;
	char			*file_name;
	char			**map;
	char			*error_message;
	float			frame;
	mlx_t			*mlx;
	t_key			keys;
	t_data			*data;
	t_vector		pos;
	t_vector		dir;
	t_vector		camera_plane;
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	mlx_texture_t	*north_t;
	mlx_texture_t	*south_t;
	mlx_texture_t	*west_t;
	mlx_texture_t	*east_t;
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

int				init_game(t_cub *game);
void			run_parse_checks(t_cub *cub, char *path);
void			test_map_child(char *path);
void			test_map(char *path);

void			init(t_cub *cub);
void			init_cub(int ac, char **av, t_cub *cub);
void			print_bad(char *path, char *msg);

void			check_file(t_cub *cub);
void			check_input(int ac, char **av, t_cub *map);

void			ft_exit(t_cub *cub, char *message, int errno);
void			ft_exit_input(char *message, int errno);

void			parsing(t_cub *cub);
void			check_textures(t_cub *cub);

void			parse_map(t_cub *cub);
void			map_error(t_cub *cub, char *message);
void			strip_line_end(char *line);
void			normalize_tabs(char *line);
int				is_line_empty(char *line);
int				is_map_char(char c);
void			flood_fill(t_cub *cub, int start_x, int start_y);
void			build_map(t_cub *cub, t_list *lines);
void			handle_player_tile(t_cub *cub, int x, int y, int *player_count);
void			check_map_tile(t_cub *cub, int x, int y, int *player_count);
void			check_map_content(t_cub *cub);
void			check_textures_open(t_cub *cub, char *path, char *msg);

void			validate_map(t_cub *cub);
int				is_map_line(char *line);
int				parse_header_line(t_cub *cub, char *line);
void			ff_free(t_ff *ff);
void			free_memory(t_cub *cub);
void			parse_texture(t_cub *cub, char **dest, char *line, int i);
void			parse_color(t_cub *cub, char **dest, char *line, int i);
int				set_texture(t_tex_set *a);
int				parse_texture_line(t_cub *cub, char *line, int i);
int				parse_color_line(t_cub *cub, char *line, int i);
int				parse_header_line(t_cub *cub, char *line);
void			setup(t_cub *game);
void			load_tex(t_cub *game);
void			hook_key_press(mlx_key_data_t key_p, void *p);
void    		hook_close(void *p);
bool			can_move_to(t_cub *game, float new_x, float new_y);
int				get_signal(float v);
t_vector		rotate_vector(t_vector v, float angle);
t_vector		create_vector(double x, double y);
t_vector		mult_vector(t_vector v, double s);
t_vector		add_vector(t_vector v1, t_vector v2);
mlx_texture_t	*init_tex(char *path);
void			draw_wall(t_cub *game, t_dda *ray, int pix);
void			draw_view(void *p);
uint32_t		get_tex_color(mlx_texture_t *tex, int y, int x);
uint32_t		parse_rgb(t_cub *cub, char *str);
void			calculate_new_pos(t_cub *game, float *new_x, float *new_y);
int				set_dir(float dir);
void			calculate_delta_dist(t_dda *ray);
void			calculate_dist_2side(t_cub *game, t_dda *ray);
void			dda_algo(t_cub *game, t_dda *ray);
void    try_move(t_cub *game, float new_x, float new_y);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:33:15 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/18 15:35:42 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define _USE_MATH_DEFINES
# include <math.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>

/* Default window resolution */
# define WIDTH	1024
# define HEIGHT	576
/* Minimap square dimension in pixels */
# define MM_PIXEL 50
/* Texture dimension in pixels */
# define TEXTURE_DIM 64
/* Scaling up wall's height (thickness) (TEXTURE_DIM * SCALE ~= 27000) */
# define SCALE 500
/* Movement Speed of the player */
# define SPEED 6
/* Rotation speed of the player */
# define ROT_SPEED 0.09
/* Field Of View */
# define FOV 70

typedef enum e_weathercock {
	N,
	E,
	S,
	W
}	t_weathercock;

/* Data structures */

typedef struct s_win {
	void	*mlx_ptr;
	void	*win_ptr;
}	t_win;

typedef struct s_img {
	t_win	*win;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	int				player_spawn_x;
	int				player_spawn_y;
	t_weathercock	player_spawn_orient;
	char			*textures[7];
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				c_color;
	int				f_color;
	char			**cube_map;
	int				max_x;
	int				max_y;
}	t_map;

typedef struct s_data {
	t_win	*win;
	t_map	*map;
	int		player_x;
	int		player_y;
	double	player_orient;
	int		player_elev;
	bool	render;
}	t_data;

/* Geometry structures */

typedef struct s_circle {
	int		x_c;
	int		y_c;
	double	r;
	int		color;
	bool	border_only;
}	t_circle;

typedef struct s_rectangle {
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
	bool	border_only;
}	t_rectangle;

/* textures.c & textures_2.c */

bool	init_textures(int fd, t_map *map);
bool	init_weathercock(t_map *map, int i, int orientation);
bool	init_color(t_map *map, int i, char color);

/* cube_map.c && cube_map2.c */

bool	init_cube_map(int fd, t_map *map);
bool	reduce_init_cube_map(t_map *map, int ret, int fd, char *line);

/* error_messages.c */

bool	error_messages(int i);

/* free_and_destroy.c */

int		free_split(char **tab);
int		free_mappy(t_map *map);
int		free_n_destroy(t_data *data);
int		free_img(t_img *img);

/* open_file.c */

bool	open_fd(char *file);

/* map_init.c */

t_map	init_struct_map(char *file);
bool	global_checker(char *file, t_map *map);

/* parsing_utils.c */

bool	str_is_digit(char *str);
bool	checkint(char *nb);

/* events.c */

int		loop_handler(t_data *data);
int		red_cross_handler(t_data *data);
int		keys_handler(int key_sym, t_data *data);

/* player_moves.c */
void	move_forward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	move_back(t_data *data);

/* draw.c */

void	draw_pixel(t_img *image, int x, int y, int color);
int		clear_img(t_img *image, int color);
t_img	*init_image(t_data *data, int width, int height);
int		get_pixel_color(int x, int y, t_img *image);
t_img	*init_image_xpm(t_data *data, char *filename);

/* cub2d.c */

void	build_minimap(t_data *data);
void	player_render(t_data *data);

/* rc_utils.c */

bool	is_wall(t_data *data, double x, double y);
double	remainder(double value, double modulus);

/* raycast_engine.c */

void	raycast_renderer(t_data *data);

#endif

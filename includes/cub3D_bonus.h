/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:18:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/24 11:58:04 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define __USE_MISC 1
# define _XOPEN_SOURCE 700
# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <float.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>

/* Default window resolution */
# define WIDTH	1024
# define HEIGHT	576
// # define WIDTH	1280
// # define HEIGHT	720
/* Minimap square dimension in pixels */
# define MM_PIXEL 100.0
/* Texture dimension in pixels */
# define TEXTURE_DIM 100.0
/* Movement Speed of the player (pixel per frame) */
# define SPEED 7.0
/* Rotation speed of the player (rad per frame) */
# define ROT_SPEED 0.07
/* Field Of View (degrees) */
# define FOV 70.0

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
	t_img			*text_no;
	t_img			*text_so;
	t_img			*text_we;
	t_img			*text_ea;
	int				c_color;
	int				f_color;
	char			**cube_map;
	int				max_x;
	int				max_y;
}	t_map;

typedef struct s_data {
	t_win	*win;
	t_map	*map;
	t_img	*pov;
	int		player_x;
	int		player_y;
	double	player_orient;
	bool	forward;
	bool	backward;
	bool	left;
	bool	right;
	bool	rot_left;
	bool	rot_right;
	bool	render;
}	t_data;

typedef struct s_point {
	double	x;
	double	y;
}	t_point;

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
t_img	*init_image_xpm(t_data *data, char *filename);
t_img	*init_image(t_data *data, int width, int height);

/* map_init.c */

t_map	init_struct_map(char *file);
void	init_data_const(t_data *data);
bool	global_checker(char *file, t_map *map);

/* parsing_utils.c */

bool	str_is_digit(char *str);
bool	checkint(char *nb);

/* events.c */

int		loop_handler(t_data *data);
int		red_cross_handler(t_data *data);
int		keys_press(int key_sym, t_data *data);
int		keys_release(int key_sym, t_data *data);

/* player_moves.c & player_moves2.c */

void	move_forward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	move_back(t_data *data);
void	rot_left(t_data *data);
void	rot_right(t_data *data);
void	move_player(t_data *data);

/* draw.c */

void	draw_pixel(t_img *image, int x, int y, int color);
int		clear_img(t_img *image, int color);
int		get_pixel_color(int x, int y, t_img *image);

/* raycast_engine.c & raycast_engine2.c */

void	raycast_renderer(t_data *data);
double	opti_rc(t_data *data, double angle,
			t_point *intersect, t_weathercock *wall_orient);

/* texturizer.c */

void	texturize_no(t_data *data, int i, int thickness, t_point *impact);
void	texturize_so(t_data *data, int i, int thickness, t_point *impact);
void	texturize_we(t_data *data, int i, int thickness, t_point *impact);
void	texturize_ea(t_data *data, int i, int thickness, t_point *impact);

/* rc_utils.c */

bool	is_wall(t_data *data, double x, double y);
double	remainder(double value, double modulus);
bool	in_map(t_data *data, double x, double y);

#endif

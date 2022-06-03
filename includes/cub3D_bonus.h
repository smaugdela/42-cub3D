/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:18:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/06/03 12:15:41 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define __USE_MISC
# define _DEFAULT_SOURCE
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
// # define WIDTH	800
// # define HEIGHT	600
# define WIDTH	1024
# define HEIGHT	576
// # define WIDTH	1280
// # define HEIGHT	720
/* Minimap square dimension in pixels */
# define MM_PIXEL 100.0
/* Texture dimension in pixels */
# define TEXTURE_DIM 100.0
/* Movement Speed of the player (pixel per frame) */
# define SPEED 8.0
/* Rotation speed of the player (rad per frame) */
# define ROT_SPEED 0.065
/* Field Of View (degrees) */
# define FOV 75.0
/* Map Parsing characters */
# define CHARMAP "01234HDMS"
/* Ennemies PV */
# define PV 3

# define SQRT_2 1.41421356237

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

typedef struct s_mob {
	t_img			*mob1;
	t_img			*mob2;
	t_img			*deadmob;
	int				pos_x;
	int				pos_y;
	bool			in_front;
	int				pv;
	double			dist;
	struct s_mob	*next;
}	t_mob;

typedef struct s_map {
	int				player_spawn_x;
	int				player_spawn_y;
	char			*textures[16];
	t_img			*w1;
	t_img			*w2;
	t_img			*w3;
	t_img			*w4;
	t_img			*house;
	t_img			*door;
	t_img			*arme1;
	t_img			*arme2;
	t_img			*attack1;
	t_img			*attack2;
	t_img			*mob1;
	t_img			*mob2;
	t_img			*deadmob;
	int				c_color;
	int				f_color;
	char			**cube_map;
	int				max_x;
	int				max_y;
	t_mob			*mobs;
}	t_map;

typedef struct s_data {
	t_win	*win;
	t_map	*map;
	t_img	*pov;
	char	*save_av;
	int		player_x;
	int		player_y;
	double	player_orient;
	bool	forward;
	bool	backward;
	bool	left;
	bool	right;
	bool	rot_left;
	bool	rot_right;
	bool	attackey;
	bool	attack;
	bool	render;
	bool	dead;
	t_img	*texture;
	double	dist[WIDTH];
}	t_data;

typedef struct s_point {
	double	x;
	double	y;
}	t_point;

int		ft_strcmp(const char *s1, const char *s2);

/* textures.c & textures_2.c */

bool	init_textures(int fd, t_map *map, t_data *data);
bool	init_weathercock(t_map *map, int i, int orientation);
bool	init_color(t_map *map, int i, char color);
bool	texture_file_check(t_img **img, t_map *map, int i, t_data *data);

/* cube_map.c && cube_map2.c */

bool	init_cube_map(int fd, t_map *map);
bool	reduce_init_cube_map(t_map *map, int ret, int fd, char *line);
t_mob	*new_mob(t_map *map, int x, int y);

/* error_messages.c */

bool	error_messages(int i);

/* free_and_destroy.c */

int		free_split(char **tab);
int		free_mappy(t_map *map);
int		free_n_destroy(t_data *data);
int		free_img(t_img *img);
void	free_mobs(t_map *map);

/* open_file.c */

bool	open_fd(char *file);
t_img	*init_image_xpm(t_data *data, char *filename);
t_img	*init_image(t_data *data, int width, int height);

/* map_init.c */

t_map	init_struct_map(char *file, t_data *data);
void	init_data_const(t_data *data);

/* parsing_utils.c */

bool	str_is_digit(char *str);
bool	checkint(char *nb);
bool	is_in_charset(char c, char *charset);
bool	tired_of_norm(int spawn);

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
void	rot_left(t_data *data, double rot_speed);
void	rot_right(t_data *data, double rot_speed);
void	move_player(t_data *data);
void	player_attack(t_data *data);
void	player_walk_anim(t_data *data);

/* player_mooves_utils */

void	player_walk_anim(t_data *data);
void	sounds_player_attacks(t_data *data);
void	is_he_ded(int i, int j, t_data *data);

/* draw.c */

void	draw_pixel(t_img *image, int x, int y, int color);
int		clear_img(t_img *image, int color);
int		get_pixel_color(int x, int y, t_img *image);
void	our_put_image_on_pov(t_data *data, t_img *texture, int x, int y);

/* raycast_engine.c & raycast_engine2.c */

void	raycast_renderer(t_data *data);
double	opti_rc(t_data *data, double angle,
			t_point *intersect, char *wall_type);
void	opti_rc_init(t_point *inter_x, t_point *inter_y);

/* texturizer.c */

void	texturizer(t_data *data, int x, int thickness, double tx);

/* rc_utils.c */

bool	is_wall(t_data *data, double x, double y, char *wall_type);
double	remainder(double value, double modulus);
bool	in_map(t_data *data, double x, double y);
int		ft_strcmp(const char *s1, const char *s2);

/* mouse_events_bonus.c */

int		pointer_handler(int x, int y, t_data *data);
int		button_press_handler(int button, int x, int y, t_data *data);
int		button_release_handler(int button, int x, int y, t_data *data);

/* bad_guys.c & bad_guys2.c */

void	render_mobs(t_data *data);
void	move_mobs(t_data *data);

/* doors.c */

void	door_manager(t_data *data);
void	win_manager(t_data *data);
void	ending_image(t_data *data);

/* sound */

int		play_sound(char *path, int volume);

#endif

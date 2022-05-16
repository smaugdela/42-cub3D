/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:33:15 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/16 17:27:36 by smagdela         ###   ########.fr       */
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
# include <math.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>

# define WIDTH	1280
# define HEIGHT	720

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
}	t_img;

typedef struct s_map
{
	int		player_pos_x;
	int		player_pos_y;
	char	player_orient;
	char	*textures[7];
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		c_color;
	int		f_color;
	char	**cube_map;
}	t_map;

typedef struct s_data {
	char	**map;
	t_win	*win;
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

/* cube_map.c */

bool	init_cube_map(int fd, t_map *map);

/* error_messages.c */

bool	error_messages(int i);

/* free_and_destroy.c */

int		free_split(char **tab);
int		free_mappy(t_map *map);

/* open_file.c */

bool	open_fd(char *file);

/* map_init.c */

t_map	init_struct_map(char *file);
bool	global_checker(char *file, t_map *map);

/* parsing_utils.c */
bool	str_is_digit(char *str);
bool	checkint(char *nb);

#endif

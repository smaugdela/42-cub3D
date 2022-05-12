/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:33:15 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/12 12:51:44 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>

# define WIDTH	1280
# define HEIGHT	720

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

#endif

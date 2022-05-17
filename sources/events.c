/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:28:10 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/17 11:34:23 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	loop_handler(t_data *data)
{
	(void)data;
	return (0);
}

int	red_cross_handler(t_data *data)
{
	free_n_destroy(data);
	ft_putstr_fd("Closing...\n\033[0;32mThanks for using cub3D!\033[0m\n", 1);
	exit(EXIT_SUCCESS);
	return (0);
}

int	keys_handler(int key_sym, t_data *data)
{
	if (key_sym == XK_Escape)
		red_cross_handler(data);
	// else if (key_sym == XK_r)
	// 	reset(image);
	// else if (key_sym == XK_h)
	// 	reset_ui(image);
	// else if (key_sym == XK_w)
	// 	zoom_in(image);
	// else if (key_sym == XK_q)
	// 	zoom_out(image);
	return (0);
}

/*
int	pointer_handler(int x, int y, t_image *image)
{
	if (image->fractal.draw_ft == &draw_julia
		&& x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		image->fractal.param.re = x
			* ((image->fractal.max_re - image->fractal.min_re)
				/ (WIN_W)) + image->fractal.min_re;
		image->fractal.param.im = (-1 * y)
			* ((image->fractal.max_im - image->fractal.min_im)
				/ (WIN_H)) + image->fractal.max_im;
		image->fractal.render = TRUE;
	}
	return (0);
}

int	button_handler(int button, int x, int y, t_image *image)
{
	(void)x;
	(void)y;
	if (button == 5)
		zoom_out(image);
	else if (button == 4)
		zoom_in(image);
	return (0);
}

Button value:
	clic gauche = 1
	clic droit = 3
	clic molette = 2
	molette /\ = 4
	molette \/ = 5
*/
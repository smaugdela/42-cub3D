/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:45:38 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/23 20:08:29 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	loop_handler(t_image *image)
{
	int	xrange[2];
	int	yrange[2];

	xrange[0] = 0;
	xrange[1] = WIN_W;
	yrange[0] = 0;
	yrange[1] = WIN_H;
	if (image->fractal.render == TRUE)
	{
		image->fractal.draw_ft(image->fractal, xrange, yrange);
		mlx_put_image_to_window(image->display->mlx_ptr,
			image->display->win_ptr, image->image_ptr, 0, 0);
		mlx_string_put(image->display->mlx_ptr, image->display->win_ptr,
			15, 20, 0xffffff, "H for help");
		image->fractal.render = FALSE;
	}
	else if (image->fractal.display_ui == TRUE)
		draw_ui(image);
	return (0);
}

void	reset_ui(t_image *image)
{
	int	xrange[2];
	int	yrange[2];

	if (image->fractal.display_ui == TRUE)
	{
		xrange[0] = WIN_W / 3 + 29;
		xrange[1] = WIN_W / 3 + 230;
		yrange[0] = WIN_H / 3 + -1;
		yrange[1] = WIN_H / 3 + 121;
		image->fractal.draw_ft(image->fractal, xrange, yrange);
		mlx_put_image_to_window(image->display->mlx_ptr,
			image->display->win_ptr, image->image_ptr, 0, 0);
		mlx_string_put(image->display->mlx_ptr, image->display->win_ptr,
			15, 20, 0x00ffffff, "H for help");
		image->fractal.display_ui = FALSE;
	}
	else
		image->fractal.display_ui = TRUE;
}

int	keys_handler(int key_sym, t_image *image)
{
	if (key_sym == XK_Escape)
		red_cross_handler(image);
	else if (key_sym == XK_h)
		reset_ui(image);
	else if (key_sym == XK_Up || key_sym == XK_Down
		|| key_sym == XK_Left || key_sym == XK_Right)
		cams(image, key_sym);
	else if (key_sym == XK_r)
		reset(image);
	else if (key_sym == XK_w)
		zoom_in(image);
	else if (key_sym == XK_q)
		zoom_out(image);
	else if (key_sym == XK_KP_Add && image->fractal.max_iter < 100)
	{
		image->fractal.max_iter += 4;
		image->fractal.render = TRUE;
	}
	else if (key_sym == XK_KP_Subtract && image->fractal.max_iter >= 10)
	{
		image->fractal.max_iter -= 4;
		image->fractal.render = TRUE;
	}
	return (0);
}

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
	if (button == 4 || button == 5)
	{
		if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		{
			if (x < WIN_W / 2 - 20)
				cams(image, XK_Left);
			else if (x > WIN_W / 2 + 20)
				cams(image, XK_Right);
			if (y < WIN_H / 2 - 20)
				cams(image, XK_Up);
			else if (y > WIN_H / 2 + 20)
				cams(image, XK_Down);
		}
		if (button == 4)
			zoom_in(image);
		else
			zoom_out(image);
	}
	return (0);
}
/*
Button value:
	clic gauche = 1
	clic droit = 3
	clic molette = 2
	molette /\ = 4
	molette \/ = 5
*/

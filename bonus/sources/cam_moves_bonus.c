/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_moves_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:49:37 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/23 13:42:47 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static void	cam_right(t_image *image, double step, int xrange[2], int yrange[2])
{
	int	stepix;
	int	x;
	int	y;

	stepix = step * WIN_W / (image->fractal.max_re - image->fractal.min_re);
	x = 0;
	while (x + stepix <= WIN_W)
	{
		y = 0;
		while (y <= WIN_H)
		{
			draw_pixel(image, x, y, get_pixel_color(x + stepix, y, image));
			++y;
		}
		++x;
	}
	image->fractal.max_re += step;
	image->fractal.min_re += step;
	xrange[0] = x - 1;
	xrange[1] = WIN_W;
	yrange[0] = 0;
	yrange[1] = WIN_H;
	image->fractal.draw_ft(image->fractal, xrange, yrange);
}

static void	cam_left(t_image *image, double step, int xrange[2], int yrange[2])
{
	int	stepix;
	int	x;
	int	y;

	stepix = step * WIN_W / (image->fractal.max_re - image->fractal.min_re);
	x = WIN_W;
	while (x - stepix >= 0)
	{
		y = 0;
		while (y <= WIN_H)
		{
			draw_pixel(image, x, y, get_pixel_color(x - stepix, y, image));
			++y;
		}
		--x;
	}
	image->fractal.max_re -= step;
	image->fractal.min_re -= step;
	xrange[0] = 0;
	xrange[1] = x + 1;
	yrange[0] = 0;
	yrange[1] = WIN_H;
	image->fractal.draw_ft(image->fractal, xrange, yrange);
}

static void	cam_up(t_image *image, double step, int xrange[2], int yrange[2])
{
	int	stepix;
	int	x;
	int	y;

	stepix = step * WIN_H / (image->fractal.max_im - image->fractal.min_im);
	x = 0;
	while (x <= WIN_W)
	{
		y = WIN_H;
		while (y - stepix >= 0)
		{
			draw_pixel(image, x, y, get_pixel_color(x, y - stepix, image));
			--y;
		}
		++x;
	}
	image->fractal.max_im += step;
	image->fractal.min_im += step;
	xrange[0] = 0;
	xrange[1] = WIN_W;
	yrange[0] = 0;
	yrange[1] = y + 1;
	image->fractal.draw_ft(image->fractal, xrange, yrange);
}

static void	cam_down(t_image *image, double step, int xrange[2], int yrange[2])
{
	int	stepix;
	int	x;
	int	y;

	stepix = step * WIN_H / (image->fractal.max_im - image->fractal.min_im);
	x = 0;
	while (x <= WIN_W)
	{
		y = 0;
		while (y + stepix <= WIN_H)
		{
			draw_pixel(image, x, y, get_pixel_color(x, y + stepix, image));
			++y;
		}
		++x;
	}
	image->fractal.max_im -= step;
	image->fractal.min_im -= step;
	xrange[0] = 0;
	xrange[1] = WIN_W;
	yrange[0] = y - 1;
	yrange[1] = WIN_H;
	image->fractal.draw_ft(image->fractal, xrange, yrange);
}

void	cams(t_image *img, int key)
{
	int	xrange[2];
	int	yrange[2];

	if (img->fractal.display_ui == TRUE)
		return ;
	else if (key == XK_Right)
		cam_right(img, 0.1 * (img->fractal.max_re - img->fractal.min_re),
			xrange, yrange);
	else if (key == XK_Left)
		cam_left(img, 0.1 * (img->fractal.max_re - img->fractal.min_re),
			xrange, yrange);
	else if (key == XK_Up)
		cam_up(img, 0.1 * (img->fractal.max_im - img->fractal.min_im),
			xrange, yrange);
	else if (key == XK_Down)
		cam_down(img, 0.1 * (img->fractal.max_im - img->fractal.min_im),
			xrange, yrange);
	else
		return ;
	img->fractal.draw_ft(img->fractal, xrange, yrange);
	mlx_put_image_to_window(img->display->mlx_ptr,
		img->display->win_ptr, img->image_ptr, 0, 0);
	mlx_string_put(img->display->mlx_ptr, img->display->win_ptr,
		15, 20, 0x00ffffff, "H for help");
}

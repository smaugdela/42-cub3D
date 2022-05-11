/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:12:02 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/23 13:51:58 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static int	ft_julia(t_complex c, t_complex param, int max_iter)
{
	int			n;
	double		tmp;

	n = 0;
	while (pow(c.re, 2) + pow(c.im, 2) < 4 && ++n < max_iter)
	{
		tmp = pow(c.re, 2) - pow(c.im, 2) + param.re;
		c.im = 2 * c.re * c.im + param.im;
		c.re = tmp;
	}
	if (n == max_iter)
		return (-1);
	else
		return (n);
}

void	draw_julia(t_fractal para, int xrange[2], int yrange[2])
{
	t_complex	c;
	int			x;
	int			y;
	int			n;

	x = xrange[0] - 1;
	while (++x < WIN_W && x <= xrange[1])
	{
		y = yrange[0] - 1;
		while (++y < WIN_H && y <= yrange[1])
		{
			c.re = x * ((para.max_re - para.min_re)
					/ (WIN_W)) + para.min_re;
			c.im = (-1 * y) * ((para.max_im - para.min_im)
					/ (WIN_H)) + para.max_im;
			n = ft_julia(c, para.param, para.max_iter);
			if (n == -1)
				draw_pixel(para.image, x, y, 0);
			else
				draw_pixel(para.image, x, y, para.color_ft(n, para.max_iter));
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multicorn_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:20:54 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/23 19:29:58 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static int	ft_multicorn(t_complex c, int max_iter)
{
	int			n;
	double		tmp;
	t_complex	z;

	n = 0;
	z.re = 0;
	z.im = 0;
	while (pow(z.re, 2) + pow(z.im, 2) < 4 && ++n < max_iter)
	{
		tmp = pow(z.re, 5) - 10 * pow(z.re, 3) * pow(z.im, 2)
			+ 5 * z.re * pow(z.im, 4) + c.re;
		z.im = -5 * pow(z.re, 4) * z.im + 10 * pow(z.re, 2) * pow(z.im, 3)
			- pow(z.im, 5) + c.im;
		z.re = tmp;
	}
	if (n == max_iter)
		return (-1);
	else
		return (n);
}

void	draw_multicorn(t_fractal para, int xrange[2], int yrange[2])
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
			n = ft_multicorn(c, para.max_iter);
			if (n == -1)
				draw_pixel(para.image, x, y, 0);
			else
				draw_pixel(para.image, x, y, para.color_ft(n, para.max_iter));
		}
		--y;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:13:58 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/23 20:02:44 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(t_image *img)
{
	float	im_amp;
	float	re_amp;

	im_amp = img->fractal.max_im - img->fractal.min_im;
	re_amp = img->fractal.max_re - img->fractal.min_re;
	img->fractal.max_im -= 0.2 * im_amp;
	img->fractal.min_im += 0.2 * im_amp;
	img->fractal.max_re -= 0.2 * re_amp;
	img->fractal.min_re += 0.2 * re_amp;
	img->fractal.render = TRUE;
}

void	zoom_out(t_image *img)
{
	float	im_amp;
	float	re_amp;

	im_amp = img->fractal.max_im - img->fractal.min_im;
	re_amp = img->fractal.max_re - img->fractal.min_re;
	img->fractal.max_im += 0.2 * im_amp;
	img->fractal.min_im -= 0.2 * im_amp;
	img->fractal.max_re += 0.2 * re_amp;
	img->fractal.min_re -= 0.2 * re_amp;
	img->fractal.render = TRUE;
}

void	reset(t_image *image)
{
	image->fractal.max_re = 2.0;
	image->fractal.min_re = -2.0;
	image->fractal.max_im = 2.0;
	image->fractal.min_im = -2.0;
	image->fractal.render = TRUE;
}

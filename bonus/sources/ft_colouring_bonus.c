/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colouring_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:49:19 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/23 13:42:40 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	get_pixel_color(int x, int y, t_image *image)
{
	char	*pixel;

	if (x > WIN_W || x < 0 || y > WIN_H || y < 0)
		return (42);
	pixel = image->addr + (y * image->size_line + x * (image->bpp / 8));
	return (*(int *)pixel);
}

int	color_bnw(int n, int max_iter)
{
	(void)n;
	(void)max_iter;
	return (0xffffff);
}

int	color_r(int n, int max_iter)
{
	int	r;

	r = -255 * ((double)n / (double)max_iter) + 255;
	return (0x010000 * r);
}

int	color_g(int n, int max_iter)
{
	int	g;

	g = -255 * ((double)n / (double)max_iter) + 255;
	return (0x000100 * g);
}

int	color_b(int n, int max_iter)
{
	int	b;

	b = -255 * ((double)n / (double)max_iter) + 255;
	return (b);
}

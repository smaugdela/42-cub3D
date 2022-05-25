/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 10:44:59 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/25 14:10:30 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_pixel(t_img *image, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x > image->width || x < 0 || y > image->height || y < 0)
	{
		ft_putstr_fd("\033[1;31mAccessing unmapped pixel.\033[0m\n", 2);
		return ;
	}
	pixel = image->addr + (y * image->size_line + x * (image->bpp / 8));
	i = image->bpp;
	while (i >= 8)
	{
		i -= 8;
		if (image->endian == 1)
			*pixel = (color >> i) & 255;
		else
			*pixel = (color >> (image->bpp - i - 8)) & 255;
		++pixel;
	}
}

int	clear_img(t_img *image, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < image->width)
	{
		j = -1;
		while (++j < image->height)
		{
			if (get_pixel_color(i, j, image) != color)
				draw_pixel(image, i, j, color);
		}
	}
	mlx_put_image_to_window(image->win->mlx_ptr,
		image->win->win_ptr, image->img_ptr, 0, 0);
	return (0);
}

int	get_pixel_color(int x, int y, t_img *image)
{
	char	*pixel;

	if (x >= image->width || x < 0 || y >= image->height || y < 0)
		return (-1);
	pixel = image->addr + (y * image->size_line + x * (image->bpp / 8));
	return (*(int *)pixel);
}
/*
void	our_put_image_to_window(t_data *data)
{
	
}
*/
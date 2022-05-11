/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:56:01 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/23 20:00:45 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_pixel(t_image *image, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x > WIN_W || x < 0 || y > WIN_H || y < 0)
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

int	clear_window(t_image *image, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIN_W)
	{
		j = -1;
		while (++j < WIN_H)
		{
			if (get_pixel_color(i, j, image) > 0)
				draw_pixel(image, i, j, color);
		}
	}
	mlx_put_image_to_window(image->display->mlx_ptr,
		image->display->win_ptr, image->image_ptr, 0, 0);
	return (0);
}

void	draw_ui(t_image *image)
{
	int		coord[2];
	int		dim[2];

	coord[0] = WIN_W / 3 + 30;
	coord[1] = WIN_H / 3;
	dim[0] = 200;
	dim[1] = 100;
	draw_rectangle(image, build_rectangle(coord, dim, 0x303030, FALSE));
	mlx_put_image_to_window(image->display->mlx_ptr,
		image->display->win_ptr, image->image_ptr, 0, 0);
	mlx_string_put(image->display->mlx_ptr, image->display->win_ptr,
		WIN_W / 2 - 30, coord[1] + 20, 0xaa00ff, "Commands:");
	mlx_string_put(image->display->mlx_ptr, image->display->win_ptr,
		WIN_W / 2 - 70, coord[1] + 40, 0x00ffaa, "Zoom: scroll wheel or Q/W");
	mlx_string_put(image->display->mlx_ptr, image->display->win_ptr,
		WIN_W / 2 - 70, coord[1] + 60, 0x00ffaa, "Details: plus/minus keys");
	mlx_string_put(image->display->mlx_ptr, image->display->win_ptr,
		WIN_W / 2 - 70, coord[1] + 80, 0x00ffaa, "Reset: R");
}

t_circle	*build_circle(int coord[2], double r, int color, t_bool bord)
{
	t_circle	*circle;

	circle = malloc(1 * sizeof(t_circle));
	if (circle == NULL)
		return (NULL);
	if (coord[0] < 0)
		circle->x_c = 0;
	else
		circle->x_c = coord[0];
	if (coord[1] < 0)
		circle->y_c = 0;
	else
		circle->y_c = coord[1];
	if (r <= 0)
		circle->r = 1;
	else
		circle->r = r;
	circle->color = color;
	circle->border_only = bord;
	return (circle);
}

void	draw_circle(t_image *image, t_circle *circle)
{
	int	i;
	int	j;

	if (circle == NULL)
	{
		free_n_destroy(image, image->display);
		ft_error("malloc");
	}
	i = circle->x_c - circle->r - 1;
	while (++i < WIN_W && i < circle->x_c + circle->r)
	{
		j = circle->y_c - circle->r - 1;
		while (++j < WIN_H && j < circle->y_c + circle->r)
		{
			if (circle->border_only == TRUE
				&& sqrt(pow(circle->x_c - i, 2) + pow(circle->y_c - j, 2))
				== circle->r)
				draw_pixel(image, i, j, circle->color);
			else if (circle->border_only == FALSE
				&& sqrt(pow(circle->x_c - i, 2) + pow(circle->y_c - j, 2))
				<= circle->r)
				draw_pixel(image, i, j, circle->color);
		}
	}
	free(circle);
}

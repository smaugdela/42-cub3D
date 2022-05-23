/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 10:44:59 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/21 15:06:27 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

t_img	*init_image(t_data *data, int width, int height)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (img == NULL || data->win == NULL)
	{
		free_n_destroy(data);
		perror("init_image");
		exit(-1);
	}
	img->win = data->win;
	img->img_ptr = mlx_new_image(data->win->mlx_ptr, width, height);
	img->addr = mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_line, &img->endian);
	if (img == NULL || img->img_ptr == NULL || img->addr == NULL)
	{
		free_img(img);
		free_n_destroy(data);
		perror("mlx_new_image");
		return (NULL);
	}
	img->width = width;
	img->height = height;
	return (img);
}

t_img	*init_image_xpm(t_data *data, char *filename)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (img == NULL || data->win == NULL)
	{
		free_n_destroy(data);
		perror("init_image");
		exit(-1);
	}
	img->win = data->win;
	img->img_ptr = mlx_xpm_file_to_image(data->win->mlx_ptr, filename,
			&img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_line, &img->endian);
	if (img == NULL || img->img_ptr == NULL || img->addr == NULL)
	{
		free_img(img);
		free_n_destroy(data);
		perror("mlx_new_image");
		return (NULL);
	}
	return (img);
}

int	get_pixel_color(int x, int y, t_img *image)
{
	char	*pixel;

	if (x >= image->width || x < 0 || y >= image->height || y < 0)
		return (-1);
	pixel = image->addr + (y * image->size_line + x * (image->bpp / 8));
	return (*(int *)pixel);
}

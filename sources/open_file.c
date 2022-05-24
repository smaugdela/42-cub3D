/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:59:17 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/24 11:44:34 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	open_fd(char *file)
{
	int		fd;
	size_t	len;

	len = ft_strlen(file);
	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (error_messages(5));
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_messages(5));
	else if ((ft_strncmp(&file[len - 4], ".cub", 4) != 0) || len <= 4)
	{
		close(fd);
		return (error_messages(5));
	}
	close(fd);
	return (true);
}

static t_img	*init_image_xpm_aux(t_data *data, t_img *img)
{
	img->addr = mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_line, &img->endian);
	if (img->addr == NULL)
	{
		free_img(img);
		ft_putstr_fd("\e[0;31mError\nmlx_get_data_addr failed\033[0m\n", 2);
		exit(-1 * free_n_destroy(data));
	}
	if (img->height != TEXTURE_DIM || img->width != TEXTURE_DIM)
		printf("\033[0;33mWarning : TEXTURE_DIM ≠ dimensions .xpm\033[0m\n");
	return (img);
}

t_img	*init_image_xpm(t_data *data, char *filename)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (img == NULL || data->win == NULL)
	{
		ft_putstr_fd("\e[0;31mError\nfailed malloc\033[0m\n", 2);
		exit(-1 * free_n_destroy(data));
	}
	img->win = data->win;
	img->img_ptr = mlx_xpm_file_to_image(data->win->mlx_ptr, filename,
			&img->width, &img->height);
	if (img->img_ptr == NULL)
	{
		free(img);
		ft_putstr_fd("\e[0;31mError\ncorrupted xpm file\033[0m\n", 2);
		exit(-1 * free_n_destroy(data));
	}
	return (init_image_xpm_aux(data, img));
}

static t_img	*init_image_aux(t_data *data, t_img *img)
{
	img->addr = mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_line, &img->endian);
	if (img->addr == NULL)
	{
		free_img(img);
		ft_putstr_fd("\e[0;31mError\nmlx_get_data_addr failed\033[0m\n", 2);
		exit(-1 * free_n_destroy(data));
	}
	return (img);
}

t_img	*init_image(t_data *data, int width, int height)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (img == NULL || data->win == NULL)
	{
		ft_putstr_fd("[0;31mError\nfailed malloc\033[0m\n", 2);
		exit(-1 * free_n_destroy(data));
	}
	img->win = data->win;
	img->img_ptr = mlx_new_image(data->win->mlx_ptr, width, height);
	if (img->img_ptr == NULL)
	{
		free_img(img);
		ft_putstr_fd("[0;31mError\nfailed mlx_new_image\033[0m\n", 2);
		exit (-1 * free_n_destroy(data));
	}
	img->width = width;
	img->height = height;
	return (init_image_aux(data, img));
}

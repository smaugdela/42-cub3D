/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:33:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/23 16:03:49 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	if (tab)
		free(tab);
	tab = NULL;
	return (1);
}

int	free_mappy(t_map *map)
{
	int	i;

	i = -1;
	if (map == NULL)
		return (1);
	while (map->textures[++i])
		free(map->textures[i]);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->ea)
		free(map->ea);
	if (map->we)
		free(map->we);
	free_img(map->text_no);
	free_img(map->text_so);
	free_img(map->text_we);
	free_img(map->text_ea);
	if (map->cube_map)
		free_split(map->cube_map);
	return (1);
}

int	free_img(t_img *img)
{
	if (img && img->img_ptr && img->win)
		mlx_destroy_image(img->win->mlx_ptr, img->img_ptr);
	if (img)
	{
		free(img);
		img = NULL;
	}
	return (1);
}

int	free_n_destroy(t_data *data)
{
	if (data->pov)
		free_img(data->pov);
	if (data->map)
		free_mappy(data->map);
	if (data->win && data->win->win_ptr)
	{
		mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);
		data->win->win_ptr = NULL;
	}
	if (data->win && data->win->mlx_ptr)
	{
		mlx_destroy_display(data->win->mlx_ptr);
		free(data->win->mlx_ptr);
		data->win->mlx_ptr = NULL;
	}
	if (data->win)
		data->win = NULL;
	return (1);
}

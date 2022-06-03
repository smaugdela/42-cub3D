/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:33:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/06/03 12:11:56 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

void	free_mobs(t_map *map)
{
	t_mob	*mob;
	t_mob	*to_free;

	mob = map->mobs;
	while (mob)
	{
		to_free = mob;
		mob = mob->next;
		free(to_free);
	}
}

int	free_mappy(t_map *map)
{
	int	i;

	i = -1;
	if (map == NULL)
		return (1);
	while (map->textures[++i])
		free(map->textures[i]);
	free_img(map->w1);
	free_img(map->w2);
	free_img(map->w3);
	free_img(map->w4);
	free_img(map->house);
	free_img(map->door);
	free_img(map->mob1);
	free_img(map->mob2);
	free_img(map->deadmob);
	free_img(map->arme1);
	free_img(map->arme2);
	free_img(map->attack1);
	free_img(map->attack2);
	free_mobs(map);
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
	data->render = 0;
	if (data->pov)
		free_img(data->pov);
	if (data->minimap)
		free_img(data->minimap);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:33:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/16 11:11:12 by smagdela         ###   ########.fr       */
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

	i = 0;
	if (map == NULL)
		return (1);
	while (map->textures && map->textures[i])
		free(map->textures[i]);
	if (map->textures)
		free(map->textures);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->ea)
		free(map->ea);
	if (map->we)
		free(map->we);
	if (map->cube_map)
		free_split(map->cube_map);
	return (1);
}

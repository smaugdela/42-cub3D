/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:51:01 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/16 11:56:06 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_map_valid(t_map *map)
{
	int	i;
	int	j;
	int size;

	i = 0;
	size = 0;
	while (map->cube_map[i++])
		size++;
	i = 0;
	while(map->cube_map[i])
	{
		j = 0;
		if (map->cube_map[0][j] != '1')
			return (false);
		if (map->cube_map[size][j])
	}
}

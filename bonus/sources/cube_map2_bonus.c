/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:49:25 by ajearuth          #+#    #+#             */
/*   Updated: 2022/06/01 14:17:26 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	reduce_init_cube_map(t_map *map, int ret, int fd, char *line)
{
	int		i;
	int		index;
	char	**tmp;

	index = 0;
	while (ret >= 0 && line && line[0])
	{
		++index;
		tmp = map->cube_map;
		map->cube_map = malloc(sizeof(char *) * (index + 1));
		if (map->cube_map == NULL)
			return (false * free_mappy(map) * free_split(tmp));
		i = 0;
		while (tmp && tmp[i])
		{
			map->cube_map[i] = ft_strdup(tmp[i]);
			++i;
		}
		map->cube_map[i] = line;
		map->cube_map[i + 1] = NULL;
		free_split(tmp);
		ret = get_next_line(fd, &line);
	}
	free(line);
	return (true);
}

t_mob	*new_mob(t_map *map, int x, int y)
{
	t_mob	*mob;

	mob = malloc(sizeof(t_mob));
	if (mob == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	mob->mob1 = map->mob1;
	mob->mob2 = map->mob2;
	mob->deadmob = map->deadmob;
	mob->pos_x = x * TEXTURE_DIM + (TEXTURE_DIM / 2);
	mob->pos_y = y * TEXTURE_DIM + (TEXTURE_DIM / 2);
	mob->pv = 3;
	mob->dist = 0;
	mob->next = NULL;
	return (mob);
}

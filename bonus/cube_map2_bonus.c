/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:49:25 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/24 11:01:06 by ajearuth         ###   ########.fr       */
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

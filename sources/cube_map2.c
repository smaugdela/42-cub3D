/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:49:25 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/17 12:00:30 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	reduce_init_cube_map(t_map *map, int ret, int fd, char *line)
{
	int		i;
	int		index;
	char	**tmp;

	i = 0;
	index = 0;
	while (ret >= 0 && line && line[0])
	{
		++index;
		tmp = map->cube_map;
		map->cube_map = malloc(sizeof(char *) * (index + 1));
		if (map->cube_map == NULL)
		{
			free_split(tmp);
			return (false * free_mappy(map));
		}
		i = -1;
		while (tmp && tmp[++i])
			map->cube_map[i] = ft_strdup(tmp[i]);
		map->cube_map[i] = line;
		map->cube_map[i + 1] = NULL;
		free_split(tmp);
		ret = get_next_line(fd, &line);
	}
	return (true);
}

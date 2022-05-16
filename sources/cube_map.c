/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:51:01 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/16 13:26:37 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_zero_sauronded(t_map *map, int i, int j)
{
	if (i == 0 || map->cube_map[i + 1] == NULL)
		return (false);
	else if (j == 0 || map->cube_map[i][j + 1] == '\0')
		return (false);
	else if (map->cube_map[i - 1][j] == ' ' || map->cube_map[i + 1][j] == ' '
		|| map->cube_map[i][j - 1] == ' ' || map->cube_map[i][j + 1] == ' ')
		return (false);
}

bool	is_map_valid(t_map *map)
{
	int		i;
	int		j;
	bool	spawn;

	if (map->cube_map == NULL || map->cube_map[0] == NULL)
		return (false);
	spawn = 0;
	i = 0;
	while (map->cube_map[i])
	{
		j = 0;
		while (map->cube_map[i][j])
		{
			if (map->cube_map[i][j] != '1' && map->cube_map[i][j] != '0'
				&& map->cube_map[i][j] != 'N' && map->cube_map[i][j] != 'E'
				&& map->cube_map[i][j] != 'S' && map->cube_map[i][j] != 'W')
				return (error_message(6));
			else if (map->cube_map[i][j] == '0' && is_zero_sauronded(map, i, j))
				return (error_message(1));
			else if (map->cube_map[i][j] == 'N' || map->cube_map[i][j] == 'E'
				|| map->cube_map[i][j] == 'S' || map->cube_map[i][j] == 'W')
			{
				if (spawn != 0)
					return (error_message(3));
				++spawn;
				map->player_pos_x = j;
				map->player_pos_y = i;
				map->player_orient = map->cube_map[i][j];
			}
			++j;
		}
		++i;
	}
	return (true);
}

bool	init_cube_map(int fd, t_map *map)
{
	char	*line;
	int		ret;
	int		index;
	char	**tmp;
	int		i;

	*line = "";
	index = 0;
	ret = 0;
	while (ret != -1 && line)
	{
		ret = get_next_line(fd, &line);
		if (!line[0])
			break ;
	}
	while (ret != -1 && line && line[0])
	{
		++index;
		tmp = map->cube_map;
		map->cube_map = malloc(sizeof(char *) * (index + 1));
		if (map->cube_map == NULL)
		{
			free_split(tmp);
			return (false * free_mappy(map));
		}
		i = 0;
		while (tmp && tmp[i])
			map->cube_map[i] = ft_strdup(tmp[i++]);
		map->cube_map[i] = ft_strdup(line);
		map->cube_map[i + 1] = NULL;
		free_split(tmp);
		ret = get_next_line(fd, &line);
	}
	return (is_map_valid(map));
}

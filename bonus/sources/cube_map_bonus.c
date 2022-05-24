/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:51:01 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/24 11:00:52 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static bool	is_zero_sauronded(t_map *map, int i, int j)
{
	if (i == 0 || map->cube_map[i + 1] == NULL)
		return (false);
	else if (j == 0 || map->cube_map[i][j + 1] == '\0')
		return (false);
	else if (map->cube_map[i - 1][j] == ' ' || map->cube_map[i + 1][j] == ' '
		|| map->cube_map[i][j - 1] == ' ' || map->cube_map[i][j + 1] == ' ')
		return (false);
	return (true);
}

static bool	conditions_map(int i, int j, t_map *map, int condition)
{
	if (condition == 1)
	{
		if (map->cube_map[i][j] != '1' && map->cube_map[i][j] != '0'
				&& map->cube_map[i][j] != 'N' && map->cube_map[i][j] != 'E'
				&& map->cube_map[i][j] != 'S' && map->cube_map[i][j] != 'W'
				&& map->cube_map[i][j] != ' ')
			return (false);
	}
	if (condition == 2)
	{
		if ((map->cube_map[i][j] == '0' || map->cube_map[i][j] == 'N'
				|| map->cube_map[i][j] == 'S' || map->cube_map[i][j] == 'W'
				|| map->cube_map[i][j] == 'E') && !is_zero_sauronded(map, i, j))
			return (false);
	}
	if (condition == 3)
	{
		if (map->cube_map[i][j] == 'N' || map->cube_map[i][j] == 'E'
				|| map->cube_map[i][j] == 'S' || map->cube_map[i][j] == 'W')
			return (false);
	}
	return (true);
}

static void	init_player_pos_n_orient(t_map *map, int i, int j)
{
	size_t	x;
	int		y;

	map->player_spawn_x = j;
	map->player_spawn_y = i;
	if (map->cube_map[i][j] == 'N')
		map->player_spawn_orient = N;
	else if (map->cube_map[i][j] == 'E')
		map->player_spawn_orient = E;
	else if (map->cube_map[i][j] == 'S')
		map->player_spawn_orient = S;
	else if (map->cube_map[i][j] == 'W')
		map->player_spawn_orient = W;
	y = 0;
	x = 0;
	while (map->cube_map[y])
	{
		if (x < ft_strlen(map->cube_map[y]))
			x = ft_strlen(map->cube_map[y]);
		++y;
	}
	map->max_x = (int)x;
	map->max_y = y;
}

static bool	is_map_valid(t_map *map)
{
	int		i;
	int		j;
	bool	spawn;

	spawn = 0;
	i = -1;
	while (map->cube_map[++i])
	{
		j = -1;
		while (map->cube_map[i][++j])
		{
			if (conditions_map(i, j, map, 1) == false)
				return (error_messages(6));
			else if (conditions_map(i, j, map, 2) == false)
				return (error_messages(1));
			else if (conditions_map(i, j, map, 3) == false)
			{
				if (spawn != 0)
					return (error_messages(3));
				++spawn;
				init_player_pos_n_orient(map, i, j);
			}
		}
	}
	return (true);
}

bool	init_cube_map(int fd, t_map *map)
{
	char	*line;
	int		ret;
	int		index;

	line = "";
	index = 0;
	ret = 0;
	while (ret != -1 && line)
	{
		ret = get_next_line(fd, &line);
		if (line[0])
			break ;
		free(line);
	}
	if (reduce_init_cube_map(map, ret, fd, line) == false)
		return (false);
	if (map->cube_map == NULL || map->cube_map[0] == NULL)
		return (false);
	return (is_map_valid(map));
}

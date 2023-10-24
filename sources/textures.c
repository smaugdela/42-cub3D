/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:54:47 by ajearuth          #+#    #+#             */
/*   Updated: 2023/10/24 16:30:40 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool check_directions(t_map *map, int i)
{
	if (ft_strncmp(map->textures[i], "NO ", 3) == 0)
	{
		if (init_weathercock(map, i, N) == false)
			return (false);
		return (true);
	}
	else if (ft_strncmp(map->textures[i], "SO ", 3) == 0)
	{
		if (init_weathercock(map, i, S) == false)
			return (false);
		return (true);
	}
	else if (ft_strncmp(map->textures[i], "WE ", 3) == 0)
	{
		if (init_weathercock(map, i, W) == false)
			return (false);
		return (true);
	}
	else if (ft_strncmp(map->textures[i], "EA ", 3) == 0)
	{
		if (init_weathercock(map, i, E) == false)
			return (false);
		return (true);
	}
	return (false);
}

static bool textures_checker_aux(t_map *map, int i)
{
	if (check_directions(map, i) == true)
		return (true);
	else if (ft_strncmp(map->textures[i], "F ", 2) == 0)
	{
		if (init_color(map, i, 'F') == false)
			return (false);
		return (true);
	}
	else if (ft_strncmp(map->textures[i], "C ", 2) == 0)
	{
		if (init_color(map, i, 'C') == false)
			return (false);
		return (true);
	}
	return (false);
}

static bool textures_checker(t_map *map)
{
	int i;

	i = -1;
	while (map->textures[++i])
	{
		if (textures_checker_aux(map, i) == false)
			return (false);
	}
	if (map->c_color == -1 || map->f_color == -1)
		return (false);
	return (true);
}

bool init_textures(int fd, t_map *map)
{
	char *line;
	int ret;
	int index;

	line = "";
	index = 0;
	ret = 1;
	while (ret > 0 && line && index < 6)
	{
		ret = get_next_line(fd, &line);
		if (line[0])
			map->textures[index++] = ft_strtrim(line, " ", "\t");
		free(line);
	}
	map->textures[index] = NULL;
	if (ret <= 0 || index < 6)
		return (false);
	else
		return (textures_checker(map));
}

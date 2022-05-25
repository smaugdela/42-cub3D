/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:54:47 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/25 13:05:41 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static bool	texture_checker_aux3(t_map *map, int i, t_data *data)
{
	if (!ft_strncmp(map->textures[i], "E1 ", 3) && !map->mob1)
		return (texture_file_check(&map->mob1, map, i, data));
	else if (!ft_strncmp(map->textures[i], "E2 ", 3) && !map->mob2)
		return (texture_file_check(&map->mob2, map, i, data));
	else if (!ft_strncmp(map->textures[i], "A1 ", 3) && !map->arme1)
		return (texture_file_check(&map->arme1, map, i, data));
	else if (!ft_strncmp(map->textures[i], "A2 ", 3) && !map->arme2)
		return (texture_file_check(&map->arme2, map, i, data));
	else if (!ft_strncmp(map->textures[i], "A3 ", 3) && !map->attack1)
		return (texture_file_check(&map->attack1, map, i, data));
	else if (!ft_strncmp(map->textures[i], "A4 ", 3) && !map->attack2)
		return (texture_file_check(&map->attack2, map, i, data));
	return (false);
}

static bool	texture_checker_aux2(t_map *map, int i, t_data *data)
{
	if (!ft_strncmp(map->textures[i], "W1 ", 3) && !map->w1)
		return (texture_file_check(&map->w1, map, i, data));
	else if (!ft_strncmp(map->textures[i], "W2 ", 3) && !map->w2)
		return (texture_file_check(&map->w2, map, i, data));
	else if (!ft_strncmp(map->textures[i], "W3 ", 3) && !map->w3)
		return (texture_file_check(&map->w3, map, i, data));
	else if (!ft_strncmp(map->textures[i], "W4 ", 3) && !map->w4)
		return (texture_file_check(&map->w4, map, i, data));
	else if (!ft_strncmp(map->textures[i], "HO ", 3) && !map->house)
		return (texture_file_check(&map->house, map, i, data));
	else if (!ft_strncmp(map->textures[i], "DO ", 3) && !map->door)
		return (texture_file_check(&map->door, map, i, data));
	return (texture_checker_aux3(map, i, data));
}

static bool	textures_checker_aux(t_map *map, int i, t_data *data)
{
	if (texture_checker_aux2(map, i, data) == true)
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

static bool	textures_checker(t_map *map, t_data *data)
{
	int	i;

	i = -1;
	while (map->textures[++i])
	{
		if (textures_checker_aux(map, i, data) == false)
			return (false);
	}
	if (map->c_color == -1 || map->f_color == -1)
		return (false);
	return (true);
}

bool	init_textures(int fd, t_map *map, t_data *data)
{
	char	*line;
	int		ret;
	int		index;

	line = "";
	index = 0;
	ret = 1;
	while (ret > 0 && line && index < 14)
	{
		ret = get_next_line(fd, &line);
		if (line[0])
			map->textures[index++] = ft_strtrim(line, " ", "\t");
		free(line);
	}
	map->textures[index] = NULL;
	if (ret <= 0 || index < 14)
		return (false);
	else
		return (textures_checker(map, data));
}

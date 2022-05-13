/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:54:47 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/13 14:36:34 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_atoc(char *str)
{}

static bool	textures_checker(t_map *map)
{
	int	i;

	i = -1;
	while (map->textures[++i])
	{
		if (ft_strncmp(map->textures[i], "NO ", 3) == 0)
			if (init_weathercock(map, i, N) == false)
				return (false);
		else if (ft_strncmp(map->textures[i], "SO ", 3) == 0)
			if (init_weathercock(map, i, S) == false)
				return (false);
		else if (ft_strncmp(map->textures[i], "WE ", 3) == 0)
			if (init_weathercock(map, i, W) == false)
				return (false);
		else if (ft_strncmp(map->textures[i], "EA ", 3) == 0)
			if (init_weathercock(map, i, E) == false)
				return (false);
		else if (ft_strncmp(map->textures[i], "F ", 2) == 0)
			map->f_color = ft_atoc(map->textures[i] + 2);
		else if (ft_strncmp(map->textures[i], "C ", 2) == 0)
			map->c_color = ft_atoc(map->textures[i] + 2);
	}
	return (true);
}

bool	init_textures(int fd, t_map *map)
{
	char	*line;
	int		ret;
	int		index;

	*line = "";
	index = 0;
	ret = 0;
	while (ret != -1 && line && index < 6)
	{
		ret = get_next_line(fd, &line);
		if (ft_strlen(line) != 0)
			map->textures[index++];
	}
	map->textures[index] = NULL;
	if (ret <= 0 || index < 6)
		return (false);
	else
		return (textures_checker(map));
}

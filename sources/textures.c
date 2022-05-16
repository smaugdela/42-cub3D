/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:54:47 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/16 14:45:56 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	checkint(char *nb)
{
	char	*int_extremum;
	int		i;

	i = 0;
	if (nb[0] == '-')
	{
		int_extremum = "-2147483648";
		i = 1;
	}
	else
		int_extremum = "2147483647";
	if (ft_strlen(nb) >= ft_strlen(int_extremum))
	{
		while (nb[i])
		{
			if (nb[i] > int_extremum[i] || !ft_isdigit(nb[i]))
				return (false);
			++i;
		}
		return (true);
	}
	else
		return (true);
}

static int	ft_atoc(char *str)
{
	char	**tab;
	int		i;
	int		r;
	int		g;
	int		b;

	tab = ft_split(str, ',');
	if (tab == NULL)
		return (-1);
	i = 0;
	while (tab[i])
	{
		if (checkint(tab[i]) == false || ft_atoi(tab[i]) > 255
			|| ft_atoi(tab[i]) < 0)
			return (-1 * free_split(tab));
		++i;
	}
	if (i != 3)
		return (-1 * free_split(tab));
	r = ft_atoi(tab[0]);
	g = ft_atoi(tab[1]);
	b = ft_atoi(tab[2]);
	free_split(tab);
	return (r * 0x010000 + g * 0x000100 + b);
}

static bool	textures_checker_aux(t_map *map, int i)
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
	else if (ft_strncmp(map->textures[i], "F ", 2) == 0)
	{
		map->f_color = ft_atoc(map->textures[i] + 2);
		return (true);
	}
	else if (ft_strncmp(map->textures[i], "C ", 2) == 0)
	{
		map->c_color = ft_atoc(map->textures[i] + 2);
		return (true);
	}
	return (false);
}

static bool	textures_checker(t_map *map)
{
	int	i;

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

bool	init_textures(int fd, t_map *map)
{
	char	*line;
	int		ret;
	int		index;

	line = "";
	index = 0;
	ret = 1;
	while (ret > 0 && line && index < 6)
	{
		ret = get_next_line(fd, &line);
		if (line[0])
			map->textures[index++] = line;
	}
	map->textures[index] = NULL;
	if (ret <= 0 || index < 6)
		return (false);
	else
		return (textures_checker(map));
}

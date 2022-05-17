/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:17:37 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/17 18:46:57 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_atoc(char *str)
{
	char	**tab;
	int		i;
	int		r;
	int		g;
	int		b;

	tab = ft_split(str, ',');
	free(str);
	if (tab == NULL)
		return (-1);
	i = 0;
	while (tab[i])
	{
		if (checkint(tab[i]) == false || str_is_digit(tab[i]) == false
			|| ft_atoi(tab[i]) > 255 || ft_atoi(tab[i]) < 0)
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

static bool	open_texture_fd(char *file)
{
	int		fd;
	size_t	len;

	len = ft_strlen(file);
	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (false);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	else if ((ft_strncmp(&file[len - 4], ".xpm", 4) != 0) || len <= 4)
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

static bool	texture_file_check(char **filepath, t_map *map, int i)
{
	*filepath = ft_strtrim(map->textures[i] + 2, " ", "\t");
	if (open_texture_fd(*filepath) == false)
		return (false);
	return (true);
}

bool	init_weathercock(t_map *map, int i, int orientation)
{
	static bool	n = 0;
	static bool	e = 0;
	static bool	s = 0;
	static bool	w = 0;

	if (orientation == N && n == 0 && ++n)
		return (texture_file_check(&map->no, map, i));
	else if (orientation == E && e == 0 && ++e)
		return (texture_file_check(&map->ea, map, i));
	else if (orientation == S && s == 0 && ++s)
		return (texture_file_check(&map->so, map, i));
	else if (orientation == W && w == 0 && ++w)
		return (texture_file_check(&map->we, map, i));
	return (false);
}

bool	init_color(t_map *map, int i, char color)
{
	static bool	f = 0;
	static bool	c = 0;
	char		*tmp;

	tmp = ft_substr(map->textures[i], 1, ft_strlen(map->textures[i]) - 1);
	if (color == 'F' && f == 0 && ++f)
	{
		map->f_color = ft_atoc(ft_strtrim(tmp, " ", "\t"));
		free(tmp);
		return (true);
	}
	else if (color == 'C' && c == 0 && ++c)
	{
		map->c_color = ft_atoc(ft_strtrim(tmp, " ", "\t"));
		free(tmp);
		return (true);
	}
	free(tmp);
	return (false);
}

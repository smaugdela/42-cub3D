/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:17:37 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/16 16:42:27 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	*filepath = ft_strtrim(map->textures[i] + 2, " ");
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

	tmp = ft_substr(map->textures[i], );
	if (color == 'F' && f == 0 && ++f)
	{
	}
	else if (color == 'C' && c == 0 && ++c)
		
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:17:37 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/16 10:58:24 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	texture_file_check(char **filepath, t_map *map, int i)
{
	*filepath = ft_strtrim(map->textures[i] + 2, " ");
	if (open_fd(*filepath) == false)
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

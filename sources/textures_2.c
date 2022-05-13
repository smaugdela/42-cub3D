/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:17:37 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/13 14:32:22 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	init_weathercock(t_map *map, int i, int orientation)
{
	static bool	n = 0;
	static bool	e = 0;
	static bool	s = 0;
	static bool	w = 0;

	if ((orientation == N && n == 1) || (orientation == E && e == 1)
		|| (orientation == S && s == 1) || (orientation == W && w == 1))
		return (false);
	if (orientation == N)
	{
		++n;
		map->no = ft_strtrim(map->textures[i] + 2, " ");
		if (open_fd(map->no) == false)
			return (false);
		return (true);
	}
	if (orientation == E)
	{
		++e;
		map->ea = ft_strtrim(map->textures[i] + 2, " ");
		if (open_fd(map->ea) == false)
			return (false);
		return (true);
	}
	if (orientation == S)
	{
		++s;
		map->so = ft_strtrim(map->textures[i] + 2, " ");
		if (open_fd(map->so) == false)
			return (false);
		return (true);
	}
	if (orientation == W)
	{
		++w;
		map->we = ft_strtrim(map->textures[i] + 2, " ");
		if (open_fd(map->we) == false)
			return (false);
		return (true);
	}
	return (false);
}

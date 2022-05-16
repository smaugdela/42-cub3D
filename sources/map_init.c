/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:55:30 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/16 13:28:09 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_map	init_struct_map(char *file)
{
	t_map	map;

	map.player_pos_x = 0;
	map.player_pos_y = 0;
	map.player_orient = '\0';
	map.textures[0] = NULL;
	map.no = NULL;
	map.so = NULL;
	map.we = NULL;
	map.ea = NULL;
	map.c_color = 0;
	map.f_color = 0;
	map.cube_map = NULL;
	if (global_checker(file, &map) == false)
	{	
		free_mappy(&map);
		exit(-1);
	}
	return (map);
}

bool	global_checker(char *file, t_map *map)
{
	int	fd;

	if (open_fd(file) == false)
		return (false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_message(5));
	if (init_textures(fd, map) == false)
		return (error_message(2));
	if (init_cube_map(fd, map) == false)
		return (false);
	return (true);
}

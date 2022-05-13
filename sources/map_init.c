/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:55:30 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/13 14:37:52 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_map	init_struct_map(char *file)
{
	t_map	map;

	if (global_checker(file, &map) == -1)
	{	
		free_mappy(&map);
		exit(-1);
	}
	get_player_pos(&map);
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
	if (init_textures(fd, map))
		return (error_message(2));
}

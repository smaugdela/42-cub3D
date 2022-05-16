/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:55:30 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/16 11:52:20 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_map	init_struct_map(char *file)
{
	t_map	map;

	map.player_pos_x = 0;
	map.player_pos_y = 0;
	map.textures[0] = NULL;
	map.no = NULL;
	map.so = NULL;
	map.we = NULL;
	map.ea = NULL;
	map.c_color = 0;
	map.f_color = 0;
	map.cube_map = NULL;
	if (global_checker(file, &map) == -1)
	{	
		free_mappy(&map);
		exit(-1);
	}
	get_player_pos(&map);
	return (map);
}

bool	init_cube_map(int fd, t_map *map)
{
	char	*line;
	int		ret;
	int		index;
	char	**tmp;
	int		i;

	*line = "";
	index = 0;
	ret = 0;
	while (ret != -1 && line)
	{
		ret = get_next_line(fd, &line);
		if (!line[0])
			break ;
	}
	while (ret != -1 && line && line[0])
	{
		++index;
		tmp = map->cube_map;
		map->cube_map = malloc(sizeof(char *) * (index + 1));
		if (map->cube_map == NULL)
		{
			free_split(tmp);
			return (false * free_mappy(map));
		}
		i = 0;
		while (tmp && tmp[i])
			map->cube_map[i] = ft_strdup(tmp[i++]);
		map->cube_map[i] = ft_strdup(line);
		map->cube_map[i + 1] = NULL;
		free_split(tmp);
		ret = get_next_line(fd, &line);
	}
	return (is_map_valid(map));
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
}

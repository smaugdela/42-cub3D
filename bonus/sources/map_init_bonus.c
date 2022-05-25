/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:55:30 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/25 14:44:11 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static bool	global_checker(char *file, t_map *map, t_data *data)
{
	int	fd;

	if (open_fd(file) == false)
		return (false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_messages(5));
	if (init_textures(fd, map, data) == false)
		return (error_messages(2));
	if (init_cube_map(fd, map) == false)
		return (false);
	return (true);
}

t_map	init_struct_map(char *file, t_data *data)
{
	t_map	map;

	map.player_spawn_x = 0;
	map.player_spawn_y = 0;
	map.textures[0] = NULL;
	map.w1 = NULL;
	map.w2 = NULL;
	map.w3 = NULL;
	map.w4 = NULL;
	map.house = NULL;
	map.door = NULL;
	map.mob1 = NULL;
	map.mob2 = NULL;
	map.arme1 = NULL;
	map.arme2 = NULL;
	map.attack1 = NULL;
	map.attack2 = NULL;
	map.c_color = 0;
	map.f_color = 0;
	map.cube_map = NULL;
	map.max_x = 0;
	map.max_y = 0;
	if (global_checker(file, &map, data) == false)
		exit(-1 * free_mappy(&map));
	return (map);
}

void	init_data_const(t_data *data)
{
	data->pov = init_image(data, WIDTH, HEIGHT);
	data->player_x = data->map->player_spawn_x * TEXTURE_DIM + TEXTURE_DIM / 2;
	data->player_y = data->map->player_spawn_y * TEXTURE_DIM + TEXTURE_DIM / 2;
	data->player_orient = M_PI_2;
	data->forward = 0;
	data->backward = 0;
	data->left = 0;
	data->right = 0;
	data->rot_left = 0;
	data->rot_right = 0;
	data->render = 1;
}

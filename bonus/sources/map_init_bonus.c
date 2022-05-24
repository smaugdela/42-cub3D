/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:55:30 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/24 11:01:38 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_map	init_struct_map(char *file)
{
	t_map	map;

	map.player_spawn_x = 0;
	map.player_spawn_y = 0;
	map.player_spawn_orient = '\0';
	map.textures[0] = NULL;
	map.no = NULL;
	map.so = NULL;
	map.we = NULL;
	map.ea = NULL;
	map.text_no = NULL;
	map.text_so = NULL;
	map.text_we = NULL;
	map.text_ea = NULL;
	map.c_color = 0;
	map.f_color = 0;
	map.cube_map = NULL;
	map.max_x = 0;
	map.max_y = 0;
	if (global_checker(file, &map) == false)
	{	
		free_mappy(&map);
		exit(-1);
	}
	return (map);
}

void	init_data_const(t_data *data)
{
	data->map->text_no = init_image_xpm(data, data->map->no);
	data->map->text_so = init_image_xpm(data, data->map->so);
	data->map->text_we = init_image_xpm(data, data->map->we);
	data->map->text_ea = init_image_xpm(data, data->map->ea);
	data->pov = init_image(data, WIDTH, HEIGHT);
	data->player_x = data->map->player_spawn_x * TEXTURE_DIM + TEXTURE_DIM / 2;
	data->player_y = data->map->player_spawn_y * TEXTURE_DIM + TEXTURE_DIM / 2;
	data->player_orient = M_PI_2 - (data->map->player_spawn_orient * M_PI_2);
	data->player_orient = remainder(data->player_orient, 2 * M_PI);
	data->forward = 0;
	data->backward = 0;
	data->left = 0;
	data->right = 0;
	data->rot_left = 0;
	data->rot_right = 0;
	data->render = 1;
}

bool	global_checker(char *file, t_map *map)
{
	int	fd;

	if (open_fd(file) == false)
		return (false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_messages(5));
	if (init_textures(fd, map) == false)
		return (error_messages(2));
	if (init_cube_map(fd, map) == false)
		return (false);
	return (true);
}

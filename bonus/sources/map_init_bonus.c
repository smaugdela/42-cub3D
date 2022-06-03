/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:55:30 by ajearuth          #+#    #+#             */
/*   Updated: 2022/06/03 14:58:40 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	init_mobs(t_map *map)
{
	t_mob	*mob;
	int		i;
	int		j;

	i = -1;
	while (++i < map->max_x)
	{
		j = -1;
		while (++j < map->max_y)
		{
			if (map->cube_map[j] && i < (int)ft_strlen(map->cube_map[j])
				&& map->cube_map[j][i] == 'M')
			{
				if (map->mobs == NULL)
					map->mobs = new_mob(map, i, j);
				else
				{
					mob = map->mobs;
					while (mob && mob->next)
						mob = mob->next;
					mob->next = new_mob(map, i, j);
				}
			}
		}
	}
}

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
	if (!init_cube_map(fd, map) || map->cube_map == NULL)
		return (false);
	init_mobs(map);
	return (true);
}

static void	init_struct_map_aux(t_map *map)
{
	map->w1 = NULL;
	map->w2 = NULL;
	map->w3 = NULL;
	map->w4 = NULL;
	map->house = NULL;
	map->door = NULL;
	map->arme1 = NULL;
	map->arme2 = NULL;
	map->attack1 = NULL;
	map->attack2 = NULL;
	map->mob1 = NULL;
	map->mob2 = NULL;
	map->deadmob = NULL;
}

t_map	init_struct_map(char *file, t_data *data)
{
	t_map	map;

	map.player_spawn_x = 0;
	map.player_spawn_y = 0;
	map.textures[0] = NULL;
	map.c_color = 0;
	map.f_color = 0;
	map.cube_map = NULL;
	map.max_x = 0;
	map.max_y = 0;
	map.mobs = NULL;
	init_struct_map_aux(&map);
	if (global_checker(file, &map, data) == false)
		exit(-1 * free_mappy(&map));
	return (map);
}

void	init_data_const(t_data *data)
{
	data->pov = init_image(data, WIDTH, HEIGHT);
	data->minimap = build_minimap(data);
	data->player = init_image_xpm(data,
			"assets/textures/textures_bonus/miniperso.xpm");
	data->player_x = data->map->player_spawn_x * TEXTURE_DIM + TEXTURE_DIM / 2;
	data->player_y = data->map->player_spawn_y * TEXTURE_DIM + TEXTURE_DIM / 2;
	data->player_orient = M_PI_2;
	data->forward = 0;
	data->backward = 0;
	data->left = 0;
	data->right = 0;
	data->rot_left = 0;
	data->rot_right = 0;
	data->attackey = 0;
	data->attack = 0;
	data->render = 1;
	data->dead = false;
	data->mmap = false;
	data->texture = NULL;
}

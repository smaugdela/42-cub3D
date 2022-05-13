/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:55:30 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/13 12:25:04 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_map	init_struct_map(char *file)
{
	t_map	map;

	get_param(&map, file);
	get_player_pos(&map);
	if (global_checker(&map) == -1)
	{	
		free_mappy(&map);
		exit(-1);
	}
	check_c(&map);
	return (map);
}

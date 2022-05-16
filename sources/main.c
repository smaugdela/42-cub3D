/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:35:44 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/16 13:38:26 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	print_map(t_map map)
{
	int	i;

	printf("--- .cub file seems valid! ---\n");
	printf(" Player spawn : X = %d, Y = %d, Cock = %c\n", map.player_pos_x,
		map.player_pos_y, map.player_orient);
	printf(" Textures : \n");
	i = 0;
	while (map.textures[i])
		printf("	- %s\n", map.textures[i++]);
	printf(" Textures files : no = %s, so = %s, we = %s, ea = %s\n",
		map.no, map.so, map.we, map.ea);
	printf(" C and F colors : C = %d, F = %d\n", map.c_color, map.f_color);
	printf(" Map description : \n");
	i = 0;
	while (map.cube_map[i])
		printf("%s\n", map.cube_map[i++]);
}

int	main(int ac, char **av)
{
	t_map	map;

	if (ac == 2)
	{
		map = init_struct_map(av[1]);
		print_map(map);
		free_mappy(&map);
	}
	else
	{
		error_message(7);
		return (-1);
	}
	return (0);
}

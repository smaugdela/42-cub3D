/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:35:44 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/17 16:59:52 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	print_map(t_map *map)
{
	int	i;

	printf("--- .cub file seems valid! ---\n");
	printf(" Player spawn : X = %d, Y = %d, Cock = %c\n", map->player_spawn_x,
		map->player_spawn_y, map->player_spawn_orient);
	printf(" Textures : \n");
	i = 0;
	while (map->textures[i])
		printf("	- %s\n", map->textures[i++]);
	printf(" Textures files : no = %s,\n so = %s,\n we = %s,\n ea = %s.\n",
		map->no, map->so, map->we, map->ea);
	printf(" C and F colors : C = %x, F = %x\n", map->c_color, map->f_color);
	printf(" Map description : \n");
	i = 0;
	while (map->cube_map[i])
		printf("%s\n", map->cube_map[i++]);
	printf(" Map dimensions : Width (x) = %d, Height (y) = %d\n",
		map->max_x, map->max_y);
}

static bool	init_win(char *win_name, t_win *window, int width, int height)
{
	window->mlx_ptr = mlx_init();
	if (window->mlx_ptr == NULL)
	{
		perror("mlx_init");
		return (false);
	}
	window->win_ptr = mlx_new_window(window->mlx_ptr,
			width, height, win_name);
	if (window->win_ptr == NULL)
	{
		mlx_destroy_display(window->mlx_ptr);
		free(window->mlx_ptr);
		window->mlx_ptr = NULL;
		perror("mlx_new_window");
		return (false);
	}
	return (true);
}

static void	init_events(t_data *data)
{
	mlx_loop_hook(data->win->mlx_ptr, &loop_handler, data);
	mlx_hook(data->win->win_ptr, DestroyNotify, StructureNotifyMask,
		&red_cross_handler, data);
	mlx_hook(data->win->win_ptr, KeyPress, KeyPressMask, &keys_handler, data);
	// mlx_hook(display->win_ptr, ButtonPress, ButtonPressMask,
	// 	&button_handler, image);
	// mlx_hook(display->win_ptr, MotionNotify, PointerMotionMask,
	// 	&pointer_handler, image);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	mappy;
	t_win	window;

	if (ac == 2)
	{
		mappy = init_struct_map(av[1]);
		data.map = &mappy;
		print_map(data.map);
		if (init_win("cub3D", &window,
				mappy.max_x * MM_PIXEL, mappy.max_y * MM_PIXEL) == false)
			return (free_mappy(data.map) * -1);
		data.win = &window;
		init_events(&data);
		data.player_elev = 0;
		data.player_orient = M_PI_2 - (data.map->player_spawn_orient * M_PI_2);
		data.player_x = data.map->player_spawn_x * MM_PIXEL + MM_PIXEL / 2;
		data.player_y = data.map->player_spawn_y * MM_PIXEL + MM_PIXEL / 2;
		mlx_loop(data.win->mlx_ptr);
		free_n_destroy(&data);
		return (0);
	}
	else
	{
		error_messages(7);
		return (-1);
	}
	return (0);
}

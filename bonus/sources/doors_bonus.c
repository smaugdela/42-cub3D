/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:10:13 by ajearuth          #+#    #+#             */
/*   Updated: 2022/06/02 17:28:52 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	ending_image(t_data *data)
{
	data->texture =	init_image_xpm(data, \
		"assets/textures/textures_bonus/youwin.xpm");
	our_put_image_on_pov(data, data->texture, 0, 0);
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->pov->img_ptr, 0, 0);
	mlx_loop(data->win->mlx_ptr);
	red_cross_handler(data);
}

void	win_manager(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = 0;
	x = data->player_x / TEXTURE_DIM;
	y = data->player_y / TEXTURE_DIM;
	while (data->map->cube_map[i])
	{
		j = 0;
		while (data->map->cube_map[i][j])
		{
			if (data->map->cube_map[i][j] == '3')
			{
				if (y == i && x >= j - 1 && x <= j + 1)
					ending_image(data);
				if (x == j && y >= i - 1 && y <= i + 1)
					ending_image(data);
			}
			j++;
		}
		i++;
	}
}

static void	open_the_door(t_data *data, int i, int j)
{
	int	x;
	int	y;

	x = data->player_x / TEXTURE_DIM;
	y = data->player_y / TEXTURE_DIM;
	if (data->map->cube_map[i][j] == 'D')
	{
		if (y == i && x >= j - 1 && x <= j + 1)
		{
			data->map->cube_map[i][j] = 'O';
			data->render = 1;
			play_sound("assets/sounds/door.wav", 100);
		}
		if (x == j && y >= i - 1 && y <= i + 1)
		{
			data->map->cube_map[i][j] = 'O';
			data->render = 1;
			play_sound("assets/sounds/door.wav", 100);
		}
	}
}

static void	close_the_door(t_data *data, int i, int j)
{
	int	x;
	int	y;

	x = data->player_x / TEXTURE_DIM;
	y = data->player_y / TEXTURE_DIM;
	if (data->map->cube_map[i][j] == 'O')
	{
		if (x > j + 1 || x < j - 1)
		{
			data->map->cube_map[i][j] = 'D';
			data->render = 1;
			play_sound("assets/sounds/door.wav", 100);
		}
		if (y > i + 1 || y < i - 1)
		{
			data->map->cube_map[i][j] = 'D';
			data->render = 1;
			play_sound("assets/sounds/door.wav", 100);
		}
	}
}

void	door_manager(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map->cube_map[i])
	{
		j = 0;
		while (data->map->cube_map[i][j])
		{
			close_the_door(data, i, j);
			open_the_door(data, i, j);
			++j;
		}
		++i;
	}
}

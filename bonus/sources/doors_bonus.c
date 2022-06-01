/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:10:13 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/31 19:42:54 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	open_the_door(t_data *data, int i, int j)
{
	int	x;
	int	y;

	x = data->player_x / TEXTURE_DIM;
	y = data->player_y / TEXTURE_DIM;
	if (data->map->cube_map[i][j] == 'D')
	{
		// printf("Closed door x = %d, y = %d, i = %d, j = %d\n", x, y, i, j);
		if (y == i && (x == j - 1 || x == j + 1 || x == j))
		{
			data->map->cube_map[i][j] = 'O';
			data->render = 1;
		}
		if (x == j && (y == i - 1 || y == i + 1 || y == j))
		{
			data->map->cube_map[i][j] = 'O';
			data->render = 1;
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
		if (x > i + 1 || x < i - 1)
		{
				data->map->cube_map[i][j] = 'D';
				data->render = 1;
		}
		if (y > j + 1 || y < j - 1)
		{
			data->map->cube_map[i][j] = 'D';
			data->render = 1;
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

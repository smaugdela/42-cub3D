/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:01:20 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/23 14:14:12 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	check_collisions(t_data *data, int move_x, int move_y)
{
	if (is_wall(data, data->player_x + move_x,
			data->player_y + move_y))
		return (true);
	if (is_wall(data, data->player_x + move_x + 1,
			data->player_y + move_y)
		|| is_wall(data, data->player_x + move_x - 1,
			data->player_y + move_y))
		return (true);
	if (is_wall(data, data->player_x + move_x,
			data->player_y + move_y + 1)
		|| is_wall(data, data->player_x + move_x,
			data->player_y + move_y - 1))
		return (true);
	if (is_wall(data, data->player_x + move_x + 1,
			data->player_y + move_y + 1)
		|| is_wall(data, data->player_x + move_x - 1,
			data->player_y + move_y + 1))
		return (true);
	if (is_wall(data, data->player_x + move_x + 1,
			data->player_y + move_y - 1)
		|| is_wall(data, data->player_x + move_x - 1,
			data->player_y + move_y - 1))
		return (true);
	return (false);
}

void	move_forward(t_data *data)
{
	int	move_x;
	int	move_y;

	move_x = cos(data->player_orient) * SPEED;
	move_y = -1 * SPEED * sin(data->player_orient);
	if (check_collisions(data, move_x, move_y) == false)
	{
		data->player_x += move_x;
		data->player_y += move_y;
		data->render = 1;
	}
}

void	move_left(t_data *data)
{
	int	move_x;
	int	move_y;

	move_x = cos(data->player_orient + M_PI_2) * SPEED;
	move_y = -1 * SPEED * sin(data->player_orient + M_PI_2);
	if (check_collisions(data, move_x, move_y) == false)
	{
		data->player_x += move_x;
		data->player_y += move_y;
		data->render = 1;
	}
}

void	move_right(t_data *data)
{
	int	move_x;
	int	move_y;

	move_x = cos(data->player_orient - M_PI_2) * SPEED;
	move_y = -1 * SPEED * sin(data->player_orient - M_PI_2);
	if (check_collisions(data, move_x, move_y) == false)
	{
		data->player_x += move_x;
		data->player_y += move_y;
		data->render = 1;
	}
}

void	move_back(t_data *data)
{
	int	move_x;
	int	move_y;

	move_x = cos(data->player_orient + M_PI) * SPEED;
	move_y = -1 * SPEED * sin(data->player_orient + M_PI);
	if (check_collisions(data, move_x, move_y) == false)
	{
		data->player_x += move_x;
		data->player_y += move_y;
		data->render = 1;
	}
}

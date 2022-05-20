/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:01:20 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/20 14:48:02 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = cos(data->player_orient) * SPEED;
	move_y = -1 * SPEED * sin(data->player_orient);
	if (!is_wall(data, data->player_x + move_x * 2,
			data->player_y + move_y * 2))
	{
		data->player_x += move_x;
		data->player_y += move_y;
	}
}

void	move_left(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = cos(data->player_orient + M_PI_2) * SPEED;
	move_y = -1 * SPEED * sin(data->player_orient + M_PI_2);
	if (!is_wall(data, data->player_x + move_x * 2,
			data->player_y + move_y * 2))
	{
		data->player_x += move_x;
		data->player_y += move_y;
	}
}

void	move_right(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = cos(data->player_orient - M_PI_2) * SPEED;
	move_y = -1 * SPEED * sin(data->player_orient - M_PI_2);
	if (!is_wall(data, data->player_x + move_x * 2,
			data->player_y + move_y * 2))
	{
		data->player_x += move_x;
		data->player_y += move_y;
	}
}

void	move_back(t_data *data)
{
	double	move_x;
	double	move_y;

	move_x = cos(data->player_orient + M_PI) * SPEED;
	move_y = -1 * SPEED * sin(data->player_orient + M_PI);
	if (!is_wall(data, data->player_x + move_x * 2,
			data->player_y + move_y * 2))
	{
		data->player_x += move_x;
		data->player_y += move_y;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:01:39 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/24 11:01:48 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	rot_left(t_data *data)
{
	data->player_orient = remainder(data->player_orient + ROT_SPEED,
			2 * M_PI);
	data->render = 1;
}

void	rot_right(t_data *data)
{
	data->player_orient = remainder(data->player_orient - ROT_SPEED,
			2 * M_PI);
	data->render = 1;
}

void	move_player(t_data *data)
{
	if (data->forward)
		move_forward(data);
	if (data->backward)
		move_back(data);
	if (data->left)
		move_left(data);
	if (data->right)
		move_right(data);
	if (data->rot_left)
		rot_left(data);
	if (data->rot_right)
		rot_right(data);
}

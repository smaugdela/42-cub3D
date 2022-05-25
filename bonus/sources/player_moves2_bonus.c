/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:01:39 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/24 15:45:24 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	rot_left(t_data *data, double rot_speed)
{
	data->player_orient = remainder(data->player_orient + rot_speed,
			2 * M_PI);
	data->render = 1;
}

void	rot_right(t_data *data, double rot_speed)
{
	data->player_orient = remainder(data->player_orient - rot_speed,
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
		rot_left(data, ROT_SPEED);
	if (data->rot_right)
		rot_right(data, ROT_SPEED);
}

void	player_attack(t_data *data)
{
	mlx_string_put(data->win->mlx_ptr, data->win->win_ptr,
		WIDTH / 3, HEIGHT / 2, 0x000000, "PAF!");
	/*
	Attack animation, with sound maybe?
	If ennemy close in front, deals damage to him.
	*/
}

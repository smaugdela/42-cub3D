/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:01:39 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/25 18:20:31 by smagdela         ###   ########.fr       */
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
		WIDTH / 2, HEIGHT / 2, 0x000000, "PAF!");
}

void	player_walk_anim(t_data *data)
{
	static int	anim = 0;

	if (anim < 9)
	{
		our_put_image_on_pov(data, data->map->arme1,
			(WIDTH / 3) + (anim % 10), (HEIGHT / 2) + (anim % 10));
		++anim;
	}
	else if (anim <= 20)
	{
		our_put_image_on_pov(data, data->map->arme2,
			(WIDTH / 3) + (10 - anim % 10), (HEIGHT / 2) + (anim % 10));
		++anim;
	}
	if (anim >= 20)
		anim = 0;
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->pov->img_ptr, 0, 0);
}

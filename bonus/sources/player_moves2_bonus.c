/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:01:39 by smagdela          #+#    #+#             */
/*   Updated: 2022/06/02 18:22:17 by smagdela         ###   ########.fr       */
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

static void	damager(t_data *data)
{
	t_mob	*mob;

	mob = data->map->mobs;
	while (mob)
	{
		if (mob->pv > 0 && mob->in_front && mob->dist > 0
			&& mob->dist <= 2 * TEXTURE_DIM)
			--mob->pv;
		mob = mob->next;
	}
}

void	player_attack(t_data *data)
{
	static int	anim = 0;

	if (anim == 0)
	{
		if (ft_strcmp(data->save_av, "assets/maps/maps_bonus/alien.cub") == 0)
			play_sound("assets/sounds/ping.wav", 80);
		else
			play_sound("assets/sounds/attack.wav", 100);
	}
	if (anim == 9)
		damager(data);
	if (anim < 9)
	{
		our_put_image_on_pov(data, data->map->attack1, (WIDTH / 3)
			+ ((anim % 10) * 0.3), (HEIGHT / 2) + ((anim % 10) * 0.3));
		++anim;
	}
	else if (anim <= 19)
	{
		our_put_image_on_pov(data, data->map->attack2, (WIDTH / 3)
			+ (5 - (anim % 10) * 0.3), (HEIGHT / 2) + ((anim % 10) * 0.3));
		++anim;
	}
	if (anim >= 19)
	{
		anim = 0;
		if (data->attackey == 0)
			data->attack = 0;
	}
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
}

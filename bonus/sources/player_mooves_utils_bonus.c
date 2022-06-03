/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mooves_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:54:13 by ajearuth          #+#    #+#             */
/*   Updated: 2022/06/03 12:13:57 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

void	sounds_player_attacks(t_data *data)
{
	if (ft_strcmp(data->save_av, "assets/maps/maps_bonus/alien.cub") == 0)
		play_sound("assets/sounds/ping.wav", 80);
	else
		play_sound("assets/sounds/attack.wav", 100);
}

void	is_he_ded(int i, int j, t_data *data)
{
	int	x;
	int	y;

	x = data->player_x / TEXTURE_DIM;
	y = data->player_y / TEXTURE_DIM;
	if (y == i && x >= j - 1 && x <= j + 1)
	{
		ending_image(data);
		data->dead = true;
	}
	if (x == j && y >= i - 1 && y <= i + 1)
	{
		ending_image(data);
		data->dead = true;
	}
}

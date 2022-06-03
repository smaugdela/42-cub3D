/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_guys2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:10:20 by smagdela          #+#    #+#             */
/*   Updated: 2022/06/02 17:57:03 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	move_mobs(t_data *data)
{
	t_point	move;
	t_mob	*mob;

	mob = data->map->mobs;
	while (mob)
	{
		move.x = 0;
		move.y = 0;
		if (mob->pv && mob->dist < 5 * TEXTURE_DIM)
		{
			if (mob->pos_x < data->player_x - 10)
				move.x = +SPEED * 0.75;
			else if (mob->pos_x > data->player_x + 10)
				move.x = -SPEED * 0.75;
			if (mob->pos_y < data->player_y - 10)
				move.y = +SPEED * 0.75;
			else if (mob->pos_y > data->player_y + 10)
				move.y = -SPEED * 0.75;
			if (move.x != 0 && move.y != 0)
			{
				move.x /= SQRT_2;
				move.y /= SQRT_2;
			}
			if (is_wall(data, mob->pos_x + move.x, mob->pos_y, NULL))
				move.x = 0;
			if (is_wall(data, mob->pos_x, mob->pos_y + move.y, NULL))
				move.y = 0;
			if (is_wall(data, mob->pos_x + move.x, mob->pos_y + move.y, NULL))
			{
				move.x = 0;
				move.y = 0;
			}
		}
		mob->pos_x += (int)move.x;
		mob->pos_y += (int)move.y;
		mob = mob->next;
	}
}

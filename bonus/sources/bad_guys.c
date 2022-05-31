/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_guys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:25:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/31 12:24:08 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	render_mobs(t_data *data)
{
	t_mob	*mob;
	double	sx;
	double	sy;
	double	sz;
	double	tmp_a;
	double	tmp_b;

	mob = data->map->mobs;
	while (mob)
	{
		if (data->player_x == mob->pos_x && data->player_y == mob->pos_y)
			mob = mob->next;
		else
		{
			sx = mob->pos_x - data->player_x;
			sy = mob->pos_y - data->player_y;
			sz = mob->pos_z;
			tmp_a = (sy * cos(data->player_orient)) + (sx * sin(data->player_orient));
			tmp_b = (sx * cos(data->player_orient) - sy * sin(data->player_orient));
			sx = tmp_a;
			sy = tmp_b;
			sx = (sx * HEIGHT / sy) + (WIDTH / 2);
			sy = (sz * HEIGHT / sy) + (HEIGHT / 2);
			if (sx >=0 && sx < WIDTH && )
			our_put_image_on_pov(data, mob->mob1, sx, sy);
			mob = mob->next;
		}
	}
}

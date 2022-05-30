/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_guys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:25:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/30 17:10:20 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	put_mob(t_data *data, double angle, int thickness, t_mob *mob)
{
	int	x;

	x = WIDTH / 2;
	angle = remainder(angle - data->player_orient, 2 * M_PI);
	x -= angle / ((FOV * M_PI / 180) / WIDTH);
	our_put_image_on_pov(data, mob->mob1,
		x - (thickness / 2), (HEIGHT - thickness) / 2);
}

static double	determine_aom(t_data *data, t_mob *mob)
{
	if (data->player_x == mob->pos_x)
	{
		if (data->player_y > mob->pos_y)
			return (-1 * M_PI_2);
		return (M_PI_2);
	}
	return (atan((double)(data->player_y - mob->pos_y)
		/ (double)(mob->pos_x - data->player_x)));
}

void	render_mobs(t_data *data)
{
	t_mob	*mob;
	double	aom;
	int		dist;
	t_point	inter;
	char	wall_type;

	inter.x = 0;
	inter.y = 0;
	wall_type = '1';
	mob = data->map->mobs;
	while (mob)
	{
		if (data->player_x == mob->pos_x && data->player_y == mob->pos_y)
			mob = mob->next;
		else
		{
			aom = determine_aom(data, mob);
			if (aom >= remainder(data->player_orient - (FOV * M_PI / 360),
					2 * M_PI)
				&& aom <= remainder(data->player_orient + (FOV * M_PI / 360),
					2 * M_PI))
			{
				dist = sqrt(pow(data->player_x - mob->pos_x, 2)
						+ pow(data->player_y - mob->pos_y, 2));
				if (dist > 0 && dist < opti_rc(data, aom, &inter, &wall_type))
				{
					put_mob(data, aom, floor(TEXTURE_DIM * HEIGHT / dist), mob);
				}
			}
			mob = mob->next;
		}
	}
}

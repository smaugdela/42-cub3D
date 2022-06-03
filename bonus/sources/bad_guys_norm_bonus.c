/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_guys_norm_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:04:33 by ajearuth          #+#    #+#             */
/*   Updated: 2022/06/03 18:31:17 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	find_pos_calcul(t_data *data, t_point *transform, t_point *plane, \
			t_mob *mob)
{
	plane->x = cos(data->player_orient - M_PI_2)
		* tan(FOV * M_PI / 360);
	plane->y = -sin(data->player_orient - M_PI_2)
		* tan(FOV * M_PI / 360);
	transform->x = (-sin(data->player_orient)
			* (mob->pos_x - data->player_x)
			- cos(data->player_orient) * (mob->pos_y - data->player_y))
		/ (plane->x * -sin(data->player_orient)
			- cos(data->player_orient) * plane->y);
	transform->y = (-plane->y * (mob->pos_x - data->player_x)
			+ plane->x * (mob->pos_y - data->player_y))
		/ (plane->x * -sin(data->player_orient)
			- cos(data->player_orient) * plane->y);
}

void	put_sprite_init(t_sprite *sprite, t_point transform)
{
	sprite->dim = (int)fabs(HEIGHT * TEXTURE_DIM / transform.y);
	sprite->step = TEXTURE_DIM / (double)sprite->dim;
	sprite->tex_pix_start.x = 0;
	sprite->tex_pix_start.y = 0;
	sprite->start.y = -sprite->dim / 2 + HEIGHT / 2;
}

void	sorter_for_mobs(t_mob *mob, t_mob *mob_far, t_mob **new_mobs)
{
	if (*new_mobs == NULL)
		*new_mobs = copy_mob(mob_far);
	else
	{
		mob = *new_mobs;
		while (mob->next)
			mob = mob->next;
		mob->next = copy_mob(mob_far);
	}
}

void	sorter_for_mobs_2(t_data *data, t_mob *mob, t_mob *mob_far)
{
	if (data->map->mobs == mob_far)
	{
		mob = data->map->mobs;
		data->map->mobs = data->map->mobs->next;
		free(mob);
	}
	else
	{
		mob = data->map->mobs;
		while (mob)
		{
			if (mob->next == mob_far)
			{
				mob->next = mob_far->next;
				free(mob_far);
			}
			mob = mob->next;
		}
	}
}

int	sort_mobs_init(t_mob *mob, t_data *data)
{
	int	nb;

	nb = 0;
	while (mob)
	{
		mob->dist = sqrt(pow(data->player_x - mob->pos_x, 2)
				+ pow(data->player_y - mob->pos_y, 2));
		++nb;
		mob->in_front = false;
		mob = mob->next;
	}
	return (nb);
}

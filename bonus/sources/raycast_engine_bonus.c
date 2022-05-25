/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:25:26 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/25 16:57:29 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	cast_a_ray(t_data *data, double alpha, int i)
{
	int				thickness;
	t_point			impact;
	char			wall_type;

	impact.x = DBL_MAX;
	impact.y = DBL_MAX;
	wall_type = '1';
	data->texture = data->map->w1;
	thickness = floor(TEXTURE_DIM * HEIGHT / (opti_rc(data, alpha, &impact,
					&wall_type) * cos(alpha - data->player_orient)));
	if (wall_type == '2')
		data->texture = data->map->w2;
	else if (wall_type == '3')
		data->texture = data->map->w3;
	else if (wall_type == '4')
		data->texture = data->map->w4;
	else if (wall_type == 'H')
		data->texture = data->map->house;
	else if (wall_type == 'D')
		data->texture = data->map->door;
	if (impact.x != DBL_MAX)
		texturizer(data, i, thickness, impact.x);
	else
		texturizer(data, i, thickness, impact.y);
}

void	raycast_renderer(t_data *data)
{
	int				i;
	double			alpha;
	double			delta_alpha;

	i = 0;
	alpha = data->player_orient + (FOV * M_PI / 360);
	delta_alpha = (FOV * M_PI / 180) / WIDTH;
	while (i < WIDTH)
	{
		cast_a_ray(data, alpha, i);
		alpha = remainder(alpha - delta_alpha, 2 * M_PI);
		++i;
	}
}

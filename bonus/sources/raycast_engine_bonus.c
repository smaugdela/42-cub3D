/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:25:26 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/25 16:11:04 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	cast_a_ray(t_data *data, double alpha, int i)
{
	int				thickness;
	t_point			impact;
	char			wall_type;
	t_img			*texture;

	impact.x = DBL_MAX;
	impact.y = DBL_MAX;
	wall_type = '1';
	texture = data->map->w1;
	thickness = floor(TEXTURE_DIM * HEIGHT / (opti_rc(data, alpha, &impact,
					&wall_type) * cos(alpha - data->player_orient)));
	if (wall_type == '2')
		texture = data->map->w2;
	else if (wall_type == '3')
		texture = data->map->w3;
	else if (wall_type == '4')
		texture = data->map->w4;
	else if (wall_type == 'H')
		texture = data->map->house;
	else if (wall_type == 'D')
		texture = data->map->door;
	if (impact.x != DBL_MAX)
		texturizer(data, i, thickness, impact.x, texture);
	else
		texturizer(data, i, thickness, impact.y, texture);
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

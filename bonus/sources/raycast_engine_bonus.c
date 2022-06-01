/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:25:26 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/31 12:43:15 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static t_img	*cast_a_ray_aux(t_data *data, char wall_type)
{
	if (wall_type == '1')
		return (data->map->w1);
	else if (wall_type == '2')
		return (data->map->w2);
	else if (wall_type == '3')
		return (data->map->w3);
	else if (wall_type == '4')
		return (data->map->w4);
	else if (wall_type == 'H')
		return (data->map->house);
	else if (wall_type == 'D')
		return (data->map->door);
	return (data->map->w1);
}

static double	cast_a_ray(t_data *data, double alpha, int i)
{
	int				thickness;
	t_point			impact;
	char			wall_type;
	double			dist;

	impact.x = DBL_MAX;
	impact.y = DBL_MAX;
	wall_type = '1';
	dist = opti_rc(data, alpha, &impact, &wall_type);
	thickness = floor(TEXTURE_DIM * HEIGHT
			/ (dist * cos(alpha - data->player_orient)));
	data->texture = cast_a_ray_aux(data, wall_type);
	if (impact.x != DBL_MAX)
		texturizer(data, i, thickness, impact.x);
	else
		texturizer(data, i, thickness, impact.y);
	return (dist);
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
		data->dist[i] = cast_a_ray(data, alpha, i);
		alpha = remainder(alpha - delta_alpha, 2 * M_PI);
		++i;
	}
}

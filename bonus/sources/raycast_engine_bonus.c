/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:25:26 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/24 11:01:51 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	cast_a_ray(t_data *data, double alpha, int i)
{
	int				thickness;
	t_point			impact;
	t_weathercock	wall_orient;

	impact.x = 0;
	impact.y = 0;
	wall_orient = N;
	thickness = floor(TEXTURE_DIM * HEIGHT / (opti_rc(data, alpha, &impact,
					&wall_orient) * cos(alpha - data->player_orient)));
	if (wall_orient == N)
		texturize_no(data, i, thickness, &impact);
	else if (wall_orient == S)
		texturize_so(data, i, thickness, &impact);
	else if (wall_orient == W)
		texturize_we(data, i, thickness, &impact);
	else if (wall_orient == E)
		texturize_ea(data, i, thickness, &impact);
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

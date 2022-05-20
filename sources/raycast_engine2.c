/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:30:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/20 20:12:59 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	rc_x(t_data *data, double angle, t_point *inter_x)
{
	int			i;
	double		dist;
	t_point		delta;

	i = data->player_x / TEXTURE_DIM;
	if ((angle >= 0 && angle < M_PI_2)
		|| (angle > 3 * M_PI_2 && angle <= 2 * M_PI))
	{
		inter_x->x = (i + 1) * TEXTURE_DIM;
		inter_x->y = data->player_y
			- (tan(angle) * (inter_x->x - data->player_x));
		dist = sqrt(pow(inter_x->x - data->player_x, 2)
				+ pow(tan(angle) * (inter_x->x - data->player_x), 2));
		delta.x = TEXTURE_DIM;
	}
	else if (angle > M_PI_2 && angle < 3 * M_PI_2)
	{
		inter_x->x = i * TEXTURE_DIM;
		inter_x->y = data->player_y
			- (tan(angle) * (data->player_x - inter_x->x));
		dist = sqrt(pow(data->player_x - inter_x->x, 2)
				+ pow(tan(angle) * (data->player_x - inter_x->x), 2));
		delta.x = -1 * TEXTURE_DIM;
	}
	else
	{
		// inter_x->x = data->player_x;
		// inter_x->y = ;
		// dist = ;
		// delta.x = 0;
		return (DBL_MAX);
	}
	delta.y = -1 * tan(angle) * TEXTURE_DIM;
	while(is_wall(data, inter_x->x, inter_x->y) == false)
	{
		inter_x->x += delta.x;
		inter_x->y += delta.y;
		dist += sqrt(pow(delta.x, 2) + pow(delta.y, 2));
		mlx_pixel_put(data->win->mlx_ptr, data->win->win_ptr, inter_x->x, inter_x->y, 0xff0000);
	}
	return (dist);
}

static double	rc_y(t_data *data, double angle, t_point *inter_y)
{
	int			j;
	double		dist;
	t_point		delta;

	j = data->player_y / TEXTURE_DIM;
	if ((angle > 0 && angle < M_PI))
	{
		inter_y->y = j * TEXTURE_DIM;
		inter_y->x = data->player_x
			+ ((data->player_y - inter_y->y) / tan(angle));
		dist = sqrt(pow((data->player_y - inter_y->y)
					/ tan(angle), 2) + pow(data->player_y - inter_y->y, 2));
		delta.y = -1 * TEXTURE_DIM;
	}
	else if (angle > M_PI && angle < 2 * M_PI)
	{
		inter_y->y = (j + 1) * TEXTURE_DIM;
		inter_y->x = data->player_x
			+ ((inter_y->y - data->player_y) / tan(angle));
		dist = sqrt(pow(inter_y->y - data->player_y, 2)
				+ pow((inter_y->y - data->player_y) / tan(angle), 2));
		delta.y = TEXTURE_DIM;
	}
	else
	{
		// inter_y->y = data->player_y;
		// inter_y->x = ;
		// dist = ;
		// delta.y = 0;
		return (DBL_MAX);
	}
	delta.x = TEXTURE_DIM / tan(angle);
	while(is_wall(data, inter_y->x, inter_y->y) == false)
	{
		inter_y->x += delta.x;
		inter_y->y += delta.y;
		dist += sqrt(pow(delta.x, 2) + pow(delta.y, 2));
		mlx_pixel_put(data->win->mlx_ptr, data->win->win_ptr, inter_y->x, inter_y->y, 0x00ff00);
	}
	return (dist);
}

double	opti_rc(t_data *data, double angle,
		t_point *intersect, t_weathercock *wall_orient)
{
	t_point			inter_x;
	t_point			inter_y;
	double			dist_x;
	double			dist_y;

	*wall_orient = N;
	inter_x.x = 0;
	inter_x.y = 0;
	inter_y.x = 0;
	inter_y.y = 0;
	dist_x = rc_x(data, angle, &inter_x);
	dist_y = rc_y(data, angle, &inter_x);
	// draw_line(data, angle, dist_x, 0xff0000);
	// draw_line(data, angle, dist_y, 0x00ff00);
	if (dist_x < dist_y)
	{
		*intersect = inter_x;
		return (dist_x);
	}
	*intersect = inter_y;
	return (dist_y);
}
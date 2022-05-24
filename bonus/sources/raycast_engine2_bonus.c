/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:30:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/24 11:01:54 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static double	rc_x_init(t_data *data, double angle,
	t_point *inter_x, t_point *delta)
{
	int	i;

	i = data->player_x / TEXTURE_DIM;
	if ((angle >= 0.0 && angle < M_PI_2)
		|| (angle > 3.0 * M_PI_2 && angle <= 2 * M_PI))
	{
		inter_x->x = (i + 1) * TEXTURE_DIM;
		inter_x->y = data->player_y
			- (tan(angle) * (inter_x->x - data->player_x));
		delta->x = TEXTURE_DIM;
		delta->y = -1 * tan(angle) * TEXTURE_DIM;
		return (sqrt(pow(inter_x->x - data->player_x, 2)
				+ pow(tan(angle) * (inter_x->x - data->player_x), 2)));
	}
	else if (angle > M_PI_2 && angle < 3 * M_PI_2)
	{
		inter_x->x = i * TEXTURE_DIM;
		inter_x->y = data->player_y
			+ (tan(angle) * (data->player_x - inter_x->x));
		delta->x = -1 * TEXTURE_DIM;
		delta->y = tan(angle) * TEXTURE_DIM;
		return (sqrt(pow(data->player_x - inter_x->x, 2)
				+ pow(tan(angle) * (data->player_x - inter_x->x), 2)));
	}
	return (DBL_MAX);
}

static double	rc_x(t_data *data, double angle,
	t_point *inter_x, t_weathercock *wall_orient)
{
	double		dist;
	t_point		delta;

	if ((angle >= 0.0 && angle < M_PI_2)
		|| (angle > 3.0 * M_PI_2 && angle <= 2 * M_PI))
		*wall_orient = W;
	else if (angle > M_PI_2 && angle < 3 * M_PI_2)
		*wall_orient = E;
	else
		return (DBL_MAX);
	dist = rc_x_init(data, angle, inter_x, &delta);
	while (!is_wall(data, inter_x->x + 1, inter_x->y)
		&& !is_wall(data, inter_x->x - 1, inter_x->y))
	{
		inter_x->x += delta.x;
		inter_x->y += delta.y;
		dist += sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	}
	return (dist);
}

static double	rc_y_init(t_data *data, double angle,
	t_point *inter_y, t_point *delta)
{
	int	j;

	j = data->player_y / TEXTURE_DIM;
	if ((angle > 0.0 && angle < M_PI))
	{
		inter_y->y = j * TEXTURE_DIM;
		inter_y->x = data->player_x
			+ ((data->player_y - inter_y->y) / tan(angle));
		delta->y = -1 * TEXTURE_DIM;
		delta->x = TEXTURE_DIM / tan(angle);
		return (sqrt(pow((data->player_y - inter_y->y)
					/ tan(angle), 2) + pow(data->player_y - inter_y->y, 2)));
	}
	else if (angle > M_PI && angle < 2 * M_PI)
	{
		inter_y->y = (j + 1) * TEXTURE_DIM;
		inter_y->x = data->player_x
			- ((inter_y->y - data->player_y) / tan(angle));
		delta->y = TEXTURE_DIM;
		delta->x = -1 * TEXTURE_DIM / tan(angle);
		return (sqrt(pow(inter_y->y - data->player_y, 2)
				+ pow((inter_y->y - data->player_y) / tan(angle), 2)));
	}
	return (DBL_MAX);
}

static double	rc_y(t_data *data, double angle,
	t_point *inter_y, t_weathercock *wall_orient)
{
	double		dist;
	t_point		delta;

	if ((angle > 0.0 && angle < M_PI))
		*wall_orient = S;
	else if (angle > M_PI && angle < 2 * M_PI)
		*wall_orient = N;
	else
		return (DBL_MAX);
	dist = rc_y_init(data, angle, inter_y, &delta);
	while (!is_wall(data, inter_y->x, inter_y->y + 1)
		&& !is_wall(data, inter_y->x, inter_y->y - 1))
	{
		inter_y->x += delta.x;
		inter_y->y += delta.y;
		dist += sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	}
	return (dist);
}

double	opti_rc(t_data *data, double angle,
		t_point *intersect, t_weathercock *wall_orient)
{
	t_point			inter_x;
	t_point			inter_y;
	t_point			dist;
	t_weathercock	orient_x;
	t_weathercock	orient_y;

	inter_x.x = 0;
	inter_x.y = 0;
	inter_y.x = 0;
	inter_y.y = 0;
	angle = remainder(angle, 2 * M_PI);
	dist.x = rc_x(data, angle, &inter_x, &orient_x);
	dist.y = rc_y(data, angle, &inter_y, &orient_y);
	if (dist.x < dist.y)
	{
		intersect->x = inter_x.x;
		intersect->y = inter_x.y;
		*wall_orient = orient_x;
		return (dist.x);
	}
	intersect->x = inter_y.x;
	intersect->y = inter_y.y;
	*wall_orient = orient_y;
	return (dist.y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:30:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/06/03 11:06:24 by smagdela         ###   ########.fr       */
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
	t_point *inter_x, char *wall_type)
{
	double	dist;
	double	step_dist;
	t_point	delta;

	if (angle == M_PI_2 || angle == 3 * M_PI_2)
		return (DBL_MAX);
	dist = rc_x_init(data, angle, inter_x, &delta);
	step_dist = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	while (!is_wall(data, inter_x->x + 1, inter_x->y, wall_type)
		&& !is_wall(data, inter_x->x - 1, inter_x->y, wall_type))
	{
		inter_x->x += delta.x;
		inter_x->y += delta.y;
		dist += step_dist;
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
	t_point *inter_y, char *wall_type)
{
	double	dist;
	double	step_dist;
	t_point	delta;

	if (angle == 0 || angle == M_PI || angle == 2 * M_PI)
		return (DBL_MAX);
	dist = rc_y_init(data, angle, inter_y, &delta);
	step_dist = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	while (!is_wall(data, inter_y->x, inter_y->y + 1, wall_type)
		&& !is_wall(data, inter_y->x, inter_y->y - 1, wall_type))
	{
		inter_y->x += delta.x;
		inter_y->y += delta.y;
		dist += step_dist;
	}
	return (dist);
}

double	opti_rc(t_data *data, double angle,
		t_point *intersect, char *wall_type)
{
	t_point	inter_x;
	t_point	inter_y;
	t_point	dist;
	char	wall_x;
	char	wall_y;

	angle = remainder(angle, 2 * M_PI);
	opti_rc_init(&inter_x, &inter_y);
	wall_x = '1';
	wall_y = '1';
	dist.x = rc_x(data, angle, &inter_x, &wall_x);
	dist.y = rc_y(data, angle, &inter_y, &wall_y);
	if (dist.x < dist.y)
	{
		intersect->y = remainder(inter_x.y, TEXTURE_DIM);
		if (angle > M_PI_2 && angle < 3 * M_PI_2)
			intersect->y = TEXTURE_DIM - intersect->y;
		*wall_type = wall_x;
		return (dist.x);
	}
	intersect->x = remainder(inter_y.x, TEXTURE_DIM);
	if (angle > M_PI && angle < 2 * M_PI)
		intersect->x = TEXTURE_DIM - intersect->x;
	*wall_type = wall_y;
	return (dist.y);
}

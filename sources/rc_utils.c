/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:59 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/18 21:44:05 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_wall(t_data *data, double x, double y)
{
	int	i;
	int	j;

	i = x / MM_PIXEL;
	j = y / MM_PIXEL;
	if (data->map->cube_map && data->map->cube_map[j]
		&& data->map->cube_map[j][i] && data->map->cube_map[j][i] == '1')
		return (true);
	return (false);
}

double	remainder(double value, double modulus)
{
	if (value >= 0.0 && value < modulus)
		return (value);
	while (value < 0.0)
		value += modulus;
	while (value >= modulus)
		value -= modulus;
	return (value);
}

/* Returns true if "gps" hits a wall, false otherwise */
bool	check_hit_x(t_data *data, double angle, t_point gps)
{
	if ((angle >= 0 && angle < M_PI_2)
		|| (angle > 3 * M_PI_2 && angle <= 2 * M_PI))
	{
		if (is_wall(data, gps.x + 1, gps.y) == true)
			return (true);
	}
	else if (angle > M_PI_2 && angle < 3 * M_PI_2)
	{
		if (is_wall(data, gps.x - 1, gps.y) == true)
			return (true);
	}
	return (false);
}

/* Returns true if "gps" hits a wall, false otherwise */
bool	check_hit_y(t_data *data, double angle, t_point gps)
{
	if (angle > 0 && angle < M_PI)
	{
		if (is_wall(data, gps.x + 1, gps.y) == true)
			return (true);
	}
	else if (angle > M_PI && angle < 2 * M_PI)
	{
		if (is_wall(data, gps.x - 1, gps.y) == true)
			return (true);
	}
	return (false);
}

/* Returns the distance to the next wall on th X axis,
	and saves the orientation of the wall being hit inside "wall_orient" */
double	next_inter_x(t_data *data, double angle,
	t_weathercock *wall_orient, t_point *gps)
{
	t_point	delta;

	gps->x = data->player_x;
	gps->y = data->player_y;
	while (check_hit_x(data, angle, *gps) == false)
	{
		if ((angle >= 0 && angle < M_PI_2)
			|| (angle > 3 * M_PI_2 && angle <= 2 * M_PI))
			delta.x = TEXTURE_DIM - remainder(gps->x, TEXTURE_DIM);
		else if (angle > M_PI_2 && angle < 3 * M_PI_2)
			delta.x = -1 * remainder(gps->x, TEXTURE_DIM);
		else
			return (DBL_MAX);
		delta.y = -1 * tan(angle) * delta.x;
		gps->x += delta.x;
		gps->y += delta.y;
	}
	if ((angle >= 0 && angle < M_PI_2)
		|| (angle > 3 * M_PI_2 && angle <= 2 * M_PI))
		*wall_orient = W;
	else if (angle > M_PI_2 && angle < 3 * M_PI_2)
		*wall_orient = E;
	return (fabs(data->player_x - gps->x) / cos(angle));
}

/* Returns the distance to the next wall on the Y axis,
	and saves the orientation of the wall being hit inside "wall_orient" */
double	next_inter_y(t_data *data, double angle,
	t_weathercock *wall_orient, t_point *gps)
{
	t_point	delta;

	gps->x = data->player_x;
	gps->y = data->player_y;
	while (check_hit_y(data, angle, *gps) == false)
	{
		if (angle > 0 && angle < M_PI)
			delta.y = TEXTURE_DIM - remainder(gps->y, TEXTURE_DIM);
		else if (angle > M_PI && angle < 2 * M_PI)
			delta.y = -1 * remainder(gps->y, TEXTURE_DIM);
		else
			return (DBL_MAX);
		delta.x = delta.y / tan(angle);
		gps->x += delta.x;
		gps->y += delta.y;
	}
	if (angle > 0 && angle < M_PI)
		*wall_orient = S;
	else if (angle > M_PI && angle < 2 * M_PI)
		*wall_orient = N;
	return (fabs(data->player_y - gps->y) / sin(angle));
}

/* Returns the distance to the next wall,
	and saves the orientation of the wall being hit inside "wall_orient" */
double	next_inter(t_data *data, double angle,
	t_weathercock *wall_orient, t_point *impact)
{
	t_point			impact_x;
	t_point			impact_y;
	double			dist_x;
	double			dist_y;
	t_weathercock	wall_orient_x;
	t_weathercock	wall_orient_y;

	dist_x = next_inter_x(data, angle, &wall_orient_x, &impact_x);
	dist_y = next_inter_y(data, angle, &wall_orient_y, &impact_y);
	if (dist_x <= dist_y)
	{
		*wall_orient = wall_orient_x;
		*impact = impact_x;
		return (dist_x);
	}
	*wall_orient = wall_orient_y;
	*impact = impact_y;
	return (dist_y);
}

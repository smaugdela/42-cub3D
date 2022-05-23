/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:59 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/21 13:23:11 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	in_map(t_data *data, double x, double y)
{
	int	i;
	int	j;

	i = trunc(x) / TEXTURE_DIM;
	j = trunc(y) / TEXTURE_DIM;
	if (i <= 0 || i >= data->map->max_x - 1
		|| j <= 0 || j >= data->map->max_y - 1)
		return (false);
	return (true);
}

bool	is_wall(t_data *data, double x, double y)
{
	int	i;
	int	j;

	i = trunc(x) / TEXTURE_DIM;
	j = trunc(y) / TEXTURE_DIM;
	if (in_map(data, x, y) == false)
		return (true);
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

// double	opti_remainder(double value, double modulus)
// {
// 	int	div;

// 	if (value >= 0.0 && value < modulus)
// 		return (value);
// 	div = value / modulus;
// 	return (value - (double)div);
// }

double	naive_raycaster(t_data *data, double angle)
{
	double	delta_x;
	double	delta_y;
	double	x;
	double	y;
	double	delta_dist;
	double	dist;

	delta_x = cos(angle);
	delta_y = -1 * sin(angle);
	x = data->player_x;
	y = data->player_y;
	dist = 0;
	delta_dist = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	while (is_wall(data, x, y) == false)
	{
		x += delta_x;
		y += delta_y;
		dist += delta_dist;
	}
	return (dist);
}

static void	texturer(double angle, t_point delta,
	t_point *intersect, t_weathercock *wall_orient)
{
	if (trunc((intersect->y - delta.y) / TEXTURE_DIM)
		!= trunc(intersect->y / TEXTURE_DIM)
		&& trunc((intersect->x - delta.x) / TEXTURE_DIM)
		!= trunc(intersect->x / TEXTURE_DIM))
		return ;
	else if (trunc((intersect->y - delta.y) / TEXTURE_DIM)
		!= trunc(intersect->y / TEXTURE_DIM))
	{
		if (angle > 0 && angle < M_PI)
			*wall_orient = S;
		else if (angle > M_PI && angle < 2 * M_PI)
			*wall_orient = N;
	}
	else if (trunc((intersect->x - delta.x) / TEXTURE_DIM)
		!= trunc(intersect->x / TEXTURE_DIM))
	{
		if ((angle >= 0 && angle < M_PI_2)
			|| (angle > 3 * M_PI_2 && angle <= 2 * M_PI))
			*wall_orient = W;
		else if (angle > M_PI_2 && angle < 3 * M_PI_2)
			*wall_orient = E;
	}
}

double	texturer_raycaster(t_data *data, double angle,
		t_point *intersect, t_weathercock *wall_orient)
{
	t_point	delta;
	double	delta_dist;
	double	dist;

	delta.x = cos(angle);
	delta.y = -1 * sin(angle);
	intersect->x = data->player_x + delta.x;
	intersect->y = data->player_y + delta.y;
	delta_dist = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	dist = delta_dist;
	while (is_wall(data, intersect->x, intersect->y) == false)
	{
		if (is_wall(data, intersect->x + delta.x, intersect->y)
			|| is_wall(data, intersect->x, intersect->y + delta.y))
		{
			intersect->x += delta.x;
			intersect->y += delta.y;
			dist += delta_dist;
			break ;
		}
		intersect->x += delta.x;
		intersect->y += delta.y;
		dist += delta_dist;
	}
	texturer(angle,delta, intersect, wall_orient);
	return (dist);
}

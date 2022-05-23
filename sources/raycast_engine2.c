/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:30:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/23 09:31:22 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	rc_x(t_data *data, double angle,
	t_point *inter_x, t_weathercock *wall_orient)
{
	int			i;
	double		dist;
	t_point		delta;

	i = data->player_x / TEXTURE_DIM;
	// mlx_pixel_put(data->win->mlx_ptr, data->win->win_ptr, data->player_x, data->player_y, 0x00ff00);
	if ((angle >= 0.0 && angle < M_PI_2)
		|| (angle > 3.0 * M_PI_2 && angle <= 2 * M_PI))
	{
		inter_x->x = (i + 1) * TEXTURE_DIM;
		inter_x->y = data->player_y
			- (tan(angle) * (inter_x->x - data->player_x));
		dist = sqrt(pow(inter_x->x - data->player_x, 2)
				+ pow(tan(angle) * (inter_x->x - data->player_x), 2));
		delta.x = TEXTURE_DIM;
		delta.y = -1 * tan(angle) * TEXTURE_DIM;
		*wall_orient = W;
	}
	else if (angle > M_PI_2 && angle < 3 * M_PI_2)
	{
		inter_x->x = i * TEXTURE_DIM;
		inter_x->y = data->player_y
			+ (tan(angle) * (data->player_x - inter_x->x));
		dist = sqrt(pow(data->player_x - inter_x->x, 2)
				+ pow(tan(angle) * (data->player_x - inter_x->x), 2));
		delta.x = -1 * TEXTURE_DIM;
		delta.y = tan(angle) * TEXTURE_DIM;
		*wall_orient = E;
	}
	else
	{
		// inter_x->x = data->player_x;
		// inter_x->y = ;
		// dist = ;
		// delta.x = 0;
		return (DBL_MAX);
	}
	while (!is_wall(data, inter_x->x + 1, inter_x->y)
		&& !is_wall(data, inter_x->x - 1, inter_x->y))
	{
		// mlx_pixel_put(data->win->mlx_ptr, data->win->win_ptr, inter_x->x, inter_x->y, 0x00ff00);
		inter_x->x += delta.x;
		inter_x->y += delta.y;
		dist += sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	}
	return (dist);
}

static double	rc_y(t_data *data, double angle,
	t_point *inter_y, t_weathercock *wall_orient)
{
	int			j;
	double		dist;
	t_point		delta;

	j = data->player_y / TEXTURE_DIM;
	// mlx_pixel_put(data->win->mlx_ptr, data->win->win_ptr, data->player_x, data->player_y, 0x00ff00);
	if ((angle > 0.0 && angle < M_PI))
	{
		inter_y->y = j * TEXTURE_DIM;
		inter_y->x = data->player_x
			+ ((data->player_y - inter_y->y) / tan(angle));
		dist = sqrt(pow((data->player_y - inter_y->y)
					/ tan(angle), 2) + pow(data->player_y - inter_y->y, 2));
		delta.y = -1 * TEXTURE_DIM;
		delta.x = TEXTURE_DIM / tan(angle);
		*wall_orient = S;
	}
	else if (angle > M_PI && angle < 2 * M_PI)
	{
		inter_y->y = (j + 1) * TEXTURE_DIM;
		inter_y->x = data->player_x
			- ((inter_y->y - data->player_y) / tan(angle));
		dist = sqrt(pow(inter_y->y - data->player_y, 2)
				+ pow((inter_y->y - data->player_y) / tan(angle), 2));
		delta.y = TEXTURE_DIM;
		delta.x = -1 * TEXTURE_DIM / tan(angle);
		*wall_orient = N;
	}
	else
	{
		// inter_y->y = data->player_y;
		// inter_y->x = ;
		// dist = ;
		// delta.y = 0;
		return (DBL_MAX);
	}
	while (!is_wall(data, inter_y->x, inter_y->y + 1)
		&& !is_wall(data, inter_y->x, inter_y->y - 1))
	{
		// mlx_pixel_put(data->win->mlx_ptr, data->win->win_ptr, inter_y->x, inter_y->y, 0x00ff00);
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
	double			dist_x;
	double			dist_y;
	t_weathercock	orient_x;
	t_weathercock	orient_y;

	inter_x.x = 0;
	inter_x.y = 0;
	inter_y.x = 0;
	inter_y.y = 0;
	angle = remainder(angle, 2 * M_PI);
	dist_x = rc_x(data, angle, &inter_x, &orient_x);
	dist_y = rc_y(data, angle, &inter_x, &orient_y);
	// draw_line(data, angle, dist_x, 0xff0000);
	// draw_line(data, angle, dist_y, 0x00ff00);
	if (dist_x < dist_y)
	{
		intersect->x = inter_x.x;
		intersect->y = inter_x.y;
		*wall_orient = orient_x;
		return (dist_x);
	}
	intersect->x = inter_y.x;
	intersect->y = inter_y.y;
	*wall_orient = orient_y;
	return (dist_y);
}

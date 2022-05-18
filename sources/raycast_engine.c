/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:25:26 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/18 16:12:07 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	naive_raycaster(t_data *data, double angle)
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

static double	opti_raycaster(t_data *data, double angle,
	t_weathercock *wall_orient)
{
	int		x;
	int		y;
	int		delta_x;
	int		delta_y;
	double	dist_y;
	double	dist_x;

	x = data->player_x;
	y = data->player_y;
	dist_x = 0;
	dist_y = 0;
	if (angle > 0 && angle < M_PI)
		delta_y = -1 * (y % TEXTURE_DIM);
	else if (angle > M_PI && angle < 2 * M_PI)
		delta_y = TEXTURE_DIM - (y % TEXTURE_DIM);
	else
		delta_y = 0;
	if ((angle >= 0 && angle < M_PI_2)
		|| (angle > 3 * M_PI_2 && angle <= 2 * M_PI))
		delta_x = TEXTURE_DIM - (x % TEXTURE_DIM);
	else if (angle > M_PI_2 && angle < 3 * M_PI_2)
		delta_x = -1 * (x % TEXTURE_DIM);
	else
		delta_x = 0;
	dist_x += abs(delta_x) / cos(angle);
	dist_y += abs(delta_y) / sin(angle);
	x += delta_x;
	y += delta_y;
	if (angle > 0 && angle < M_PI && is_wall(data, x, y + 1))
	{
		
	}
	else if (angle > M_PI && angle < 2 * M_PI && is_wall(data, x, y - 1))
	{
		
	}
	if ((angle >= 0 && angle) < M_PI_2
		|| (angle > 3 * M_PI_2 && angle <= 2 * M_PI) && is_wall(data, x + 1, y))
	{
		
	}
	else if (angle > M_PI_2 && angle < 3 * M_PI_2 && is_wall(data, x - 1, y))
	{
		
	}
}

static void	draw_pixel_column(t_data *data, int i, int thickness, t_img *pov)
{
	int	y;

	y = 0;
	while (y < (HEIGHT - thickness) / 2 && y < HEIGHT)
		draw_pixel(pov, i, y++, data->map->c_color);
	while (y < (HEIGHT + thickness) / 2 && y < HEIGHT)
		draw_pixel(pov, i, y++, 0x014506);
	while (y < HEIGHT)
		draw_pixel(pov, i, y++, data->map->f_color);
}

void	raycast_renderer(t_data *data)
{
	t_img			*pov;
	double 			alpha;
	double			delta_alpha;
	int				i;
	int				thickness;
	t_weathercock	wall_orient;

	pov = init_image(data, WIDTH, HEIGHT);
	alpha = data->player_orient - (FOV * M_PI / 360);
	delta_alpha = (FOV * M_PI / 180) / WIDTH;
	i = 0;
	while (i < WIDTH)
	{
		thickness = TEXTURE_DIM * SCALE / naive_raycaster(data, alpha);
		draw_pixel_column(data, i, thickness, pov);
		alpha += delta_alpha;
		++i;
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		pov->img_ptr, 0, 0);
	free_img(pov);
}

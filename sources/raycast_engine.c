/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:25:26 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/21 15:18:40 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_pixel_column(t_data *data, int i, double thickness,
	t_img *pov, t_img *texture, int column)
{
	int		y;
	int		color;
	double	row;
	double	step;

	y = 0;
	row = 0;
	if (thickness == 0)
		step = 0;
	else
		step = TEXTURE_DIM / (double)thickness;
	while (y < (HEIGHT - thickness) / 2 && y < HEIGHT)
		draw_pixel(pov, i, y++, data->map->c_color);
	while (y < (HEIGHT + thickness) / 2 && y < HEIGHT)
	{
		color = get_pixel_color(column, trunc(row), texture);
		row += step;
		draw_pixel(pov, i, y++, color);
	}
	while (y < HEIGHT)
		draw_pixel(pov, i, y++, data->map->f_color);
}

void	raycast_renderer(t_data *data)
{
	t_img			*pov;
	t_img			*wall;
	double 			alpha;
	double			delta_alpha;
	int				i;
	int				j;
	double			thickness;
	t_weathercock	wall_orient;
	t_point			impact;

	pov = init_image(data, WIDTH, HEIGHT);
	alpha = data->player_orient + (FOV * M_PI / 360);
	delta_alpha = (FOV * M_PI / 180) / WIDTH;
	i = 0;
	wall_orient = N;
	while (i < WIDTH)
	{
		thickness = TEXTURE_DIM * SCALE / (opti_rc(data, 
					alpha, &impact, &wall_orient) * cos(alpha - data->player_orient));
		// thickness = TEXTURE_DIM * SCALE / texturer_raycaster(data, 
		// 		alpha, &impact, &wall_orient);
		// thickness = TEXTURE_DIM * SCALE / naive_raycaster(data, alpha);
		if (wall_orient == N)
		{
			j = TEXTURE_DIM - impact.x;
			wall = init_image_xpm(data, data->map->no);
			draw_pixel_column(data, i, thickness, pov, wall, j);
			free_img(wall);
		}
		if (wall_orient == S)
		{
			j = impact.x;
			wall = init_image_xpm(data, data->map->so);
			draw_pixel_column(data, i, thickness, pov, wall, j);
			free_img(wall);
		}
		if (wall_orient == W)
		{
			j = impact.y;
			wall = init_image_xpm(data, data->map->we);
			draw_pixel_column(data, i, thickness, pov, wall, j);
			free_img(wall);
		}
		if (wall_orient == E)
		{
			j = TEXTURE_DIM - impact.y;
			wall = init_image_xpm(data, data->map->ea);
			draw_pixel_column(data, i, thickness, pov, wall, j);
			free_img(wall);
		}
		alpha = remainder(alpha - delta_alpha, 2 * M_PI);
		++i;
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		pov->img_ptr, 0, 0);
	free_img(pov);
}

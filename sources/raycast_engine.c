/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:25:26 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/20 17:29:16 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_pixel_column(t_data *data, int i, double thickness,
	t_img *pov, int color)
{
	int	y;

	y = 0;
	while (y < (HEIGHT - thickness) / 2 && y < HEIGHT)
		draw_pixel(pov, i, y++, data->map->c_color);
	while (y < (HEIGHT + thickness) / 2 && y < HEIGHT)
		draw_pixel(pov, i, y++, color);
	while (y < HEIGHT)
		draw_pixel(pov, i, y++, data->map->f_color);
}

void	raycast_renderer(t_data *data)
{
	t_img			*pov;
	double 			alpha;
	double			delta_alpha;
	int				i;
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
		thickness = TEXTURE_DIM * SCALE / texturer_raycaster(data, 
				alpha, &impact, &wall_orient);
		// thickness = TEXTURE_DIM * SCALE / naive_raycaster(data, alpha);
		if (wall_orient == N)
			draw_pixel_column(data, i, thickness, pov, 0xeb7d34);
		if (wall_orient == S)
			draw_pixel_column(data, i, thickness, pov, 0xeb3483);
		if (wall_orient == W)
			draw_pixel_column(data, i, thickness, pov, 0xa27cd9);
		if (wall_orient == E)
			draw_pixel_column(data, i, thickness, pov, 0x7cd9d6);
		alpha = remainder(alpha - delta_alpha, 2 * M_PI);
		++i;
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		pov->img_ptr, 0, 0);
	free_img(pov);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturizer_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:42:34 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/25 18:21:04 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

// static void	draw_pixel_column(t_data *data, int x, int thickness,
// 		t_img *texture, double tx)
// {
// 	int		y;
// 	int		color;
// 	double	ty;
// 	double	ty_step;

// 	y = 0;
// 	ty = 0;
// 	ty_step = 0;
// 	if (thickness != 0)
// 		ty_step = TEXTURE_DIM / (double)thickness;
// 	if (thickness > HEIGHT)
// 	{
// 		ty += ((thickness - HEIGHT) / 2.0) * ty_step;
// 		thickness = HEIGHT;
// 	}
// 	while (y < (HEIGHT - thickness) / 2 && y < HEIGHT)
// 		draw_pixel(data->pov, x, y++, data->map->c_color);
// 	while (y < (HEIGHT + thickness) / 2 && ty < TEXTURE_DIM && y < HEIGHT)
// 	{
// 		color = get_pixel_color(floor(tx), floor(ty), texture);
// 		draw_pixel(data->pov, x, y++, color);
// 		ty += ty_step;
// 	}
// 	while (y < HEIGHT)
// 		draw_pixel(data->pov, x, y++, data->map->f_color);
// }

void	texturizer(t_data *data, int x, int thickness, double tx)
{
	int		y;
	int		color;
	double	ty;
	double	ty_step;

	y = 0;
	ty = 0;
	ty_step = 0;
	if (thickness != 0)
		ty_step = TEXTURE_DIM / (double)thickness;
	if (thickness >= HEIGHT)
		ty += ((thickness - HEIGHT) / 2.0) * ty_step;
	while (y < (HEIGHT - thickness) / 2 && y < HEIGHT)
		draw_pixel(data->pov, x, y++, data->map->c_color);
	while (y < (HEIGHT + thickness) / 2 && ty < TEXTURE_DIM && y < HEIGHT)
	{
		color = get_pixel_color(floor(tx), floor(ty), data->texture);
		draw_pixel(data->pov, x, y++, color);
		ty += ty_step;
	}
	while (y < HEIGHT)
		draw_pixel(data->pov, x, y++, data->map->f_color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:51:40 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/23 14:52:22 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
cub2D, minimap renderer
*/
// int	loop_handler(t_data *data)
// {
// 	if (data->render)
// 	{
// 		build_minimap(data);
// 		player_render(data);
// 		data->render = 0;
// 	}
// 	return (0);
// }

/*
int	pointer_handler(int x, int y, t_image *image)
{
	if (image->fractal.draw_ft == &draw_julia
		&& x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		image->fractal.param.re = x
			* ((image->fractal.max_re - image->fractal.min_re)
				/ (WIN_W)) + image->fractal.min_re;
		image->fractal.param.im = (-1 * y)
			* ((image->fractal.max_im - image->fractal.min_im)
				/ (WIN_H)) + image->fractal.max_im;
		image->fractal.render = TRUE;
	}
	return (0);
}

int	button_handler(int button, int x, int y, t_image *image)
{
	(void)x;
	(void)y;
	if (button == 5)
		zoom_out(image);
	else if (button == 4)
		zoom_in(image);
	return (0);
}

Button value:
	clic gauche = 1
	clic droit = 3
	clic molette = 2
	molette /\ = 4
	molette \/ = 5
*/
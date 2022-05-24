/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:47:26 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/24 15:40:44 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	pointer_handler(int x, int y, t_data *data)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		if (x > WIDTH / 2)
		{
			rot_right(data, ROT_SPEED * 0.35);
			mlx_mouse_move(data->win->mlx_ptr, data->win->win_ptr,
				WIDTH / 2, HEIGHT / 2);
		}
		else if (x < WIDTH / 2)
		{
			rot_left(data, ROT_SPEED * 0.35);
			mlx_mouse_move(data->win->mlx_ptr, data->win->win_ptr,
				WIDTH / 2, HEIGHT / 2);
		}
		else
			mlx_mouse_move(data->win->mlx_ptr, data->win->win_ptr,
				x, HEIGHT / 2);
	}
	return (0);
}

int	button_handler(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		player_attack(data);
	return (0);
}
/*
Button value:
	clic gauche = 1
	clic droit = 3
	clic molette = 2
	molette /\ = 4
	molette \/ = 5
*/

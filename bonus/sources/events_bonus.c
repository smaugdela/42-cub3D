/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:51:40 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/24 16:27:17 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
cub3D game loop
*/
int	loop_handler(t_data *data)
{
	int	anim;

	anim = 1;
	if (data->render)
	{
		raycast_renderer(data);
		mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
			data->pov->img_ptr, 0, 0);
		data->render = 0;
		if (anim == 1)
		{
			our_put_image_to_window(data);
			anim = 2;
		}
		if (anim == 2)
		{
			our_put_image_to_window(data);
			anim = 1;
		}
	}
	move_player(data);
	return (0);
}

int	red_cross_handler(t_data *data)
{
	free_n_destroy(data);
	ft_putstr_fd("Closing...\n\033[0;32mThanks for using cub3D!\033[0m\n", 1);
	exit(EXIT_SUCCESS);
	return (0);
}

int	keys_press(int key_sym, t_data *data)
{
	if (key_sym == XK_Escape)
		red_cross_handler(data);
	else if (key_sym == XK_space)
		player_attack(data);
	else if (key_sym == XK_w)
		data->forward = 1;
	else if (key_sym == XK_d)
		data->right = 1;
	else if (key_sym == XK_a)
		data->left = 1;
	else if (key_sym == XK_s)
		data->backward = 1;
	else if (key_sym == XK_Left)
		data->rot_left = 1;
	else if (key_sym == XK_Right)
		data->rot_right = 1;
	return (0);
}

int	keys_release(int key_sym, t_data *data)
{
	if (key_sym == XK_w)
		data->forward = 0;
	else if (key_sym == XK_d)
		data->right = 0;
	else if (key_sym == XK_a)
		data->left = 0;
	else if (key_sym == XK_s)
		data->backward = 0;
	else if (key_sym == XK_Left)
		data->rot_left = 0;
	else if (key_sym == XK_Right)
		data->rot_right = 0;
	return (0);
}

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
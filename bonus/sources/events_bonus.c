/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:51:40 by smagdela          #+#    #+#             */
/*   Updated: 2022/06/03 12:32:30 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	check_death(t_data *data)
{
	t_mob	*mob;

	mob = data->map->mobs;
	while (mob)
	{
		if (mob->pv && mob->dist < TEXTURE_DIM / 2)
		{
			data->texture =	init_image_xpm(data, \
				"assets/textures/textures_bonus/youloose.xpm");
			our_put_image_on_pov(data, data->texture, 0, 0);
			mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
				data->pov->img_ptr, 0, 0);
			data->render = 0;
			data->dead = true;
			break ;
		}
		mob = mob->next;
	}
}

/*
cub3D game loop
*/
int	loop_handler(t_data *data)
{
	if (data->dead == false)
	{
		if (data->render || data->attack)
		{
			door_manager(data);
			win_manager(data);
			raycast_renderer(data);
			move_mobs(data);
			render_mobs(data);
			if (data->attack)
				player_attack(data);
			else
				player_walk_anim(data);
			our_put_image_on_pov(data, data->minimap, 0, 0);
			player_render(data, 0, 0);
			mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
				data->pov->img_ptr, 0, 0);
			check_death(data);
			data->render = 0;
		}
		move_player(data);
	}
	return (0);
}

int	red_cross_handler(t_data *data)
{
	system("killall paplay");
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
	{
		data->attackey = 1;
		data->attack = 1;
	}
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
	if (key_sym == XK_space)
		data->attackey = 0;
	else if (key_sym == XK_w)
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

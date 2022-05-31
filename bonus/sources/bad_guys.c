/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_guys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:25:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/31 17:02:19 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	put_sprite_to_pov(t_data *data, t_point transform)
{
	t_point	start;
	t_point	stop;
	t_point	scrn_pix;
	t_point	tex_pix;
	int		sprite_dim;
	int		color;

	sprite_dim = (int)fabs(HEIGHT * TEXTURE_DIM / transform.y);
	start.y = -sprite_dim / 2 + HEIGHT / 2;
	if (start.y < 0)
		start.y = 0;
	stop.y = sprite_dim / 2 + HEIGHT / 2;
	if (stop.y >= HEIGHT)
		stop.y = HEIGHT - 1;
	start.x = ((WIDTH / 2) * (1 + transform.x / transform.y)) - (sprite_dim / 2);
	if (start.x < 0)
		start.x = 0;
	stop.x = (sprite_dim / 2) + ((WIDTH / 2) * (1 + transform.x / transform.y));
	if (stop.x >= WIDTH)
		stop.x = WIDTH - 1;
	tex_pix.x = 0;
	scrn_pix.x = start.x;
	while (scrn_pix.x < stop.x && scrn_pix.x >= 0 && scrn_pix.x < WIDTH)
	{
		tex_pix.y = 0;
		scrn_pix.y = start.y;
		while (scrn_pix.y < stop.y && scrn_pix.y >=0 && scrn_pix.y < HEIGHT
			&& transform.y > 0 && transform.y < data->dist[(int)scrn_pix.x])
		{
			color = get_pixel_color(trunc(tex_pix.x),
					trunc(tex_pix.y), data->texture);
			if ((color & 0xff000000) == 0)
				draw_pixel(data->pov, scrn_pix.x, scrn_pix.y, color);
			++scrn_pix.y;
			tex_pix.y += TEXTURE_DIM / sprite_dim;
		}
		tex_pix.x += TEXTURE_DIM / sprite_dim;
		++scrn_pix.x;
	}
}

// void	put_sprite_to_pov(t_data *data, t_point screen, int dim, double trans_y)
// {
// 	int		color;
// 	double	tx;
// 	double	ty;
// 	double	step;
// 	int		start_y;

// 	start_y = screen.y;
// 	step = (double)data->texture->height / (HEIGHT / 2);
// 	tx = 0;
// 	while (screen.x >= 0 && screen.x < WIDTH && tx < data->texture->width)
// 	{
// 		screen.y = start_y;
// 		ty = 0;
// 		while (trans_y > 0 && trans_y < data->dist[screen.x]
// 			&& screen.y >= 0 && screen.y < HEIGHT && ty < data->texture->height)
// 		{
// 			color = get_pixel_color(trunc(tx),
// 					trunc(ty), data->texture);
// 			if ((color & 0xff000000) == 0)
// 				draw_pixel(data->pov, screen.x, screen.y, color);
// 			++screen.y;
// 			ty += step;
// 		}
// 		++screen.x;
// 		tx += step;
// 	}
// }

void	render_mobs(t_data *data)
{
	t_mob	*mob;
	t_point	transform;
	t_point	plane;

	mob = data->map->mobs;
	while (mob)
	{
		if (data->player_x == mob->pos_x && data->player_y == mob->pos_y)
			mob = mob->next;
		else
		{
			plane.x = cos(data->player_orient - M_PI_2)
				* tan(FOV * M_PI / 360);
			plane.y = -sin(data->player_orient - M_PI_2)
				* tan(FOV * M_PI / 360);
			transform.x = (-sin(data->player_orient)
					* (mob->pos_x - data->player_x)
					- cos(data->player_orient) * (mob->pos_y - data->player_y))
				/ (plane.x * -sin(data->player_orient)
					- cos(data->player_orient) * plane.y);
			transform.y = (-plane.y * (mob->pos_x - data->player_x)
					+ plane.x * (mob->pos_y - data->player_y))
				/ (plane.x * -sin(data->player_orient)
					- cos(data->player_orient) * plane.y);
			data->texture = mob->mob1;
			put_sprite_to_pov(data, transform);
			mob = mob->next;
		}
	}
}

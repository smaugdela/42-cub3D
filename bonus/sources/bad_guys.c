/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_guys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:25:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/31 16:07:43 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	put_sprite_to_pov(t_data *data, t_point sprite, t_point transform)
{
	t_point	start;
	t_point	stop;
	t_point	pixel;
	int		sprite_dim;

	sprite_dim = (int)abs(HEIGHT / transform.y);
	start.y = -sprite_dim / 2 + HEIGHT / 2;
	if (start.y < 0)
		start.y = 0;
	stop.y = sprite_dim / 2 + HEIGHT / 2;
	if (stop.y >= HEIGHT)
		stop.y = HEIGHT - 1;
	start.x = -sprite_dim / 2 + (WIDTH / 2) * (1 + transform.x / transform.y);
	if (start.x < 0)
		start.x = 0;
	stop.x = sprite_dim / 2 + (WIDTH / 2) * (1 + transform.x / transform.y);
	if (stop.x >= WIDTH)
		stop.x = WIDTH - 1;
	pixel.x = start.x;
	while (pixel.x < stop.x && pixel.x >= 0 && pixel.x < WIDTH)
	{
		pixel.y = start.y;
		while (pixel.y < stop.y && pixel.y >=0 &&pixel.y < HEIGHT
			&& transform.y > 0 && transform.y < data->dist[pixel.x])
		{
			++pixel.y;
		}
		++pixel.x;
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
	t_point	sprite;
	t_point	transform;
	t_point	plane;

	mob = data->map->mobs;
	while (mob)
	{
		if (data->player_x == mob->pos_x && data->player_y == mob->pos_y)
			mob = mob->next;
		else
		{
			sprite.x = mob->pos_x - data->player_x;
			sprite.y = mob->pos_y - data->player_y;
			plane.x = cos(data->player_orient - M_PI_2)
				* tan(FOV * M_PI / 360);
			plane.y = -sin(data->player_orient - M_PI_2)
				* tan(FOV * M_PI / 360);
			transform.x = invDet * (-sin(data->player_orient) * sprite.x
					- cos(data->player_orient) * sprite.y) / (plane.x
					* -sin(data->player_orient)
					- cos(data->player_orient) * plane.y);
			transform.y = invDet * (-plane.y * sprite.x
					+ plane.x * sprite.y) / (plane.x * -sin(data->player_orient)
					- cos(data->player_orient) * plane.y);
			data->texture = mob->mob1;
			put_sprite_to_pov(data, sprite, transform);
			mob = mob->next;
		}
	}
}

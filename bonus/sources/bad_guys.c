/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_guys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:25:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/06/01 14:34:40 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static t_mob	*copy_mob(t_mob *mob_orig)
{
	t_mob	*mob_copy;

	mob_copy = malloc(sizeof(t_mob));
	if (mob_copy == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	mob_copy->mob1 = mob_orig->mob1;
	mob_copy->mob2 = mob_orig->mob2;
	mob_copy->deadmob = mob_orig->deadmob;
	mob_copy->pos_x = mob_orig->pos_x;
	mob_copy->pos_y = mob_orig->pos_y;
	mob_copy->pv = mob_orig->pv;
	mob_copy->dist = mob_orig->dist;
	mob_copy->next = NULL;
	return (mob_copy);
}

static void	sort_mobs(t_data *data)
{
	t_mob	*mob;
	t_mob	*mob_far;
	t_mob	*new_mobs;
	int		nb;

	nb = 0;
	mob = data->map->mobs;
	new_mobs = NULL;
	while (mob)
	{
		mob->dist = pow(data->player_x - mob->pos_x, 2)
			+ pow(data->player_y - mob->pos_y, 2);
		++nb;
		mob = mob->next;
	}
	while (nb--)
	{
		mob = data->map->mobs;
		mob_far = mob;
		while (mob)
		{
			if (mob->dist > mob_far->dist)
				mob_far = mob;
			mob = mob->next;
		}
		if (new_mobs == NULL)
			new_mobs = copy_mob(mob_far);
		else
		{
			mob = new_mobs;
			while (mob->next)
				mob = mob->next;
			mob->next = copy_mob(mob_far);
		}
		if (data->map->mobs == mob_far)
		{
			mob = data->map->mobs;
			data->map->mobs = data->map->mobs->next;
			free(mob);
		}
		else
		{
			mob = data->map->mobs;
			while (mob)
			{
				if (mob->next == mob_far)
				{
					mob->next = mob_far->next;
					free(mob_far);
				}
				mob = mob->next;
			}
		}
	}
	free_mobs(data->map);
	data->map->mobs = new_mobs;
}

static void	put_sprite_to_pov(t_data *data, t_point transform)
{
	t_point	start;
	t_point	stop;
	t_point	scrn_pix;
	t_point	tex_pix_start;
	t_point	tex_pix;
	double	step;
	int		sprite_dim;
	int		color;

	sprite_dim = (int)fabs(HEIGHT * TEXTURE_DIM / transform.y);
	step = TEXTURE_DIM / sprite_dim;
	tex_pix_start.x = 0;
	tex_pix_start.y = 0;
	start.y = -sprite_dim / 2 + HEIGHT / 2;
	if (start.y < 0)
	{
		tex_pix_start.y = fabs(start.y * step);
		start.y = 0;
	}
	stop.y = sprite_dim / 2 + HEIGHT / 2;
	if (stop.y >= HEIGHT)
		stop.y = HEIGHT - 1;
	start.x = ((WIDTH / 2) * (1 + transform.x / transform.y))
		- (sprite_dim / 2);
	if (start.x < 0)
	{
		tex_pix_start.x = fabs(start.x * step);
		start.x = 0;
	}
	stop.x = (sprite_dim / 2) + ((WIDTH / 2) * (1 + transform.x / transform.y));
	if (stop.x >= WIDTH)
		stop.x = WIDTH - 1;
	scrn_pix.x = start.x;
	tex_pix.x = tex_pix_start.x;
	while (scrn_pix.x < stop.x && scrn_pix.x >= 0 && scrn_pix.x < WIDTH)
	{
		tex_pix.y = tex_pix_start.y;
		scrn_pix.y = start.y;
		while (scrn_pix.y < stop.y && scrn_pix.y >=0 && scrn_pix.y < HEIGHT
			&& transform.y > 0 && transform.y < data->dist[(int)scrn_pix.x])
		{
			color = get_pixel_color(trunc(tex_pix.x),
					trunc(tex_pix.y), data->texture);
			if ((color & 0xff000000) == 0)
				draw_pixel(data->pov, scrn_pix.x, scrn_pix.y, color);
			++scrn_pix.y;
			tex_pix.y += step;
		}
		tex_pix.x += step;
		++scrn_pix.x;
	}
}

void	render_mobs(t_data *data)
{
	t_mob	*mob;
	t_point	transform;
	t_point	plane;

	sort_mobs(data);
	mob = data->map->mobs;
	while (mob)
	{
		if (!(data->player_x == mob->pos_x && data->player_y == mob->pos_y))
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
		}
		mob = mob->next;
	}
}

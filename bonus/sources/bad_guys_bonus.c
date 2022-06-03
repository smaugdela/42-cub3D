/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_guys_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:25:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/06/03 18:30:58 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_mob	*copy_mob(t_mob *mob_orig)
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
	mob_copy->in_front = mob_orig->in_front;
	mob_copy->pv = mob_orig->pv;
	mob_copy->dist = mob_orig->dist;
	mob_copy->next = NULL;
	return (mob_copy);
}

static void	print_sprite(t_data *data, t_mob *mob, t_sprite sprite,
	t_point transform)
{
	if (WIDTH / 2 > sprite.start.x && WIDTH / 2 < sprite.stop.x)
		mob->in_front = true;
	while (sprite.scrn_pix.x < sprite.stop.x
		&& sprite.scrn_pix.x >= 0 && sprite.scrn_pix.x < WIDTH)
	{
		sprite.tex_pix.y = sprite.tex_pix_start.y;
		sprite.scrn_pix.y = sprite.start.y;
		while (sprite.scrn_pix.y < sprite.stop.y
			&& sprite.scrn_pix.y >= 0 && sprite.scrn_pix.y < HEIGHT
			&& transform.y < data->dist[(int)sprite.scrn_pix.x])
		{
			sprite.color = get_pixel_color(trunc(sprite.tex_pix.x),
					trunc(sprite.tex_pix.y), data->texture);
			if ((sprite.color & 0xff000000) == 0)
				draw_pixel(data->pov, sprite.scrn_pix.x,
					sprite.scrn_pix.y, sprite.color);
			++sprite.scrn_pix.y;
			sprite.tex_pix.y += sprite.step;
		}
		sprite.tex_pix.x += sprite.step;
		++sprite.scrn_pix.x;
	}
}

void	sort_mobs(t_data *data)
{
	t_mob	*mob;
	t_mob	*mob_far;
	t_mob	*new_mobs;
	int		nb;

	mob = data->map->mobs;
	new_mobs = NULL;
	nb = sort_mobs_init(mob, data);
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
		sorter_for_mobs(mob, mob_far, &new_mobs);
		sorter_for_mobs_2(data, mob, mob_far);
	}
	free_mobs(data->map);
	data->map->mobs = new_mobs;
}

void	put_sprite_to_pov(t_data *data, t_point transform, t_mob *mob)
{
	t_sprite	sprite;

	put_sprite_init(&sprite, transform);
	if (sprite.start.y < 0)
	{
		sprite.tex_pix_start.y = fabs(sprite.start.y * sprite.step);
		sprite.start.y = 0;
	}
	sprite.stop.y = sprite.dim / 2 + HEIGHT / 2;
	if (sprite.stop.y >= HEIGHT)
		sprite.stop.y = HEIGHT - 1;
	sprite.start.x = ((WIDTH / 2) * (1 + transform.x / transform.y))
		- (sprite.dim / 2);
	if (sprite.start.x < 0)
	{
		sprite.tex_pix_start.x = fabs(sprite.start.x * sprite.step);
		sprite.start.x = 0;
	}
	sprite.stop.x = (sprite.dim / 2) + ((WIDTH / 2)
			* (1 + transform.x / transform.y));
	if (sprite.stop.x >= WIDTH)
		sprite.stop.x = WIDTH - 1;
	sprite.scrn_pix.x = sprite.start.x;
	sprite.tex_pix.x = sprite.tex_pix_start.x;
	print_sprite(data, mob, sprite, transform);
}

void	render_mobs(t_data *data)
{
	t_mob			*mob;
	t_point			transform;
	t_point			plane;
	static int		anim = 0;

	sort_mobs(data);
	mob = data->map->mobs;
	while (mob)
	{
		if (!(data->player_x == mob->pos_x && data->player_y == mob->pos_y))
		{
			find_pos_calcul(data, &transform, &plane, mob);
			if (mob->pv <= 0)
				data->texture = mob->deadmob;
			else if (anim < 15 && anim > 5)
				data->texture = mob->mob1;
			else
				data->texture = mob->mob2;
			if (transform.y > 0)
				put_sprite_to_pov(data, transform, mob);
		}
		mob = mob->next;
	}
	if (++anim >= 20)
		anim = 0;
}

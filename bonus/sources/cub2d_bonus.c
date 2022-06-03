/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub2d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:56:24 by smagdela          #+#    #+#             */
/*   Updated: 2022/06/03 18:41:42 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

// static double	raydrawer(t_data *data, double angle, int color)
// {
// 	double	delta_x;
// 	double	delta_y;
// 	double	x;
// 	double	y;
// 	double	dist;

// 	delta_x = cos(angle);
// 	delta_y = -1 * sin(angle);
// 	x = data->player_x;
// 	y = data->player_y;
// 	dist = 0;
// 	while (is_wall(data, x, y) == false)
// 	{
// 		x += delta_x;
// 		y += delta_y;
// 		++dist;
// 		mlx_pixel_put(data->win->mlx_ptr, data->win->win_ptr, x, y, color);
// 	}
// 	return (dist);
// }

// void	draw_line(t_data *data, double angle, double dist, int color)
// {
// 	t_point	delta;
// 	t_point	a;

// 	a.x = data->player_x;
// 	a.y = data->player_y;
// 	delta.x = cos(angle);
// 	delta.y = -1 * sin(angle);
// 	while (dist > 0 && in_map(data, a.x, a.y))
// 	{
// 		mlx_pixel_put(data->win->mlx_ptr, data->win->win_ptr, a.x, a.y, color);
// 		a.x += delta.x;
// 		a.y += delta.y;
// 		--dist;
// 	}
// }

void	put_minimap(t_data *data)
{
	int	x;
	int	y;
	int	wall_dim;

	wall_dim = ft_min((int)WIDTH
			/ data->map->max_x, (int)HEIGHT / data->map->max_y);
	x = ((double)data->player_x
			/ (data->map->max_x * TEXTURE_DIM)) * data->map->max_x * wall_dim;
	y = ((double)data->player_y
			/ (data->map->max_y * TEXTURE_DIM)) * data->map->max_y * wall_dim;
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		data->minimap->img_ptr, 0, 0);
	mlx_put_image_to_window(data->win->mlx_ptr,
		data->win->win_ptr, data->player->img_ptr,
		x - (data->player->width / 2), y - (data->player->height / 2));
}

static void	put_wall_to_minimap(t_img *minimap, t_ipoint grid,
	int color, int wall_dim)
{
	int	x;
	int	y;

	x = grid.x * wall_dim;
	while (x < (grid.x + 1) * wall_dim)
	{
		y = grid.y * wall_dim;
		while (y < (grid.y + 1) * wall_dim)
		{
			draw_pixel(minimap, x, y, color);
			++y;
		}
		++x;
	}
}

static t_img	*init_build_minimap(int *color, t_data *data, int *wall_dim)
{
	if (ft_strcmp(data->save_av, "assets/maps/maps_bonus/alien.cub") == 0)
		*color = 0xaaaaaa;
	else
		*color = 0x8c7b50;
	*wall_dim = ft_min((int)WIDTH / data->map->max_x, \
		(int)HEIGHT / data->map->max_y);
	return (init_image(data, WIDTH, HEIGHT));
}

t_img	*build_minimap(t_data *data)
{
	t_img		*minimap;
	t_ipoint	grd;
	int			wall_dim;
	int			color;

	minimap = init_build_minimap(&color, data, &wall_dim);
	grd.y = -1;
	while (++grd.y < data->map->max_y && data->map->cube_map[grd.y])
	{
		grd.x = -1;
		while (++grd.x < data->map->max_x
			&& data->map->cube_map[grd.y][grd.x] != '\0')
		{
			if (data->map->cube_map[grd.y][grd.x]
				&& is_in_charset(data->map->cube_map[grd.y][grd.x], "1234HD "))
			{
				if (data->map->cube_map[grd.y][grd.x] == 'D')
					put_wall_to_minimap(minimap, grd, 0xcc122b, wall_dim);
				else
					put_wall_to_minimap(minimap, grd, color, wall_dim);
			}
		}
	}
	return (minimap);
}

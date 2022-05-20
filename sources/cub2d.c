/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:56:24 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/20 20:13:11 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
// 		dist += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
// 		mlx_pixel_put(data->win->mlx_ptr, data->win->win_ptr, x, y, color);
// 	}
// 	return (dist);
// }

void	draw_line(t_data *data, double angle, double dist, int color)
{
	t_point	delta;
	t_point	a;

	a.x = data->player_x;
	a.y = data->player_y;
	delta.x = cos(angle);
	delta.y = -1 * sin(angle);
	while (dist > 0 && in_map(data, a.x, a.y))
	{
		mlx_pixel_put(data->win->mlx_ptr, data->win->win_ptr, a.x, a.y, color);
		a.x += delta.x;
		a.y += delta.y;
		dist -= 1;
	}
}

void	player_render(t_data *data)
{
	t_img			*player;
	double 			alpha;
	double			delta_alpha;
	int				i;
	t_point			impact;
	t_weathercock	wall_orient;

	// alpha = data->player_orient - (FOV * M_PI / 360);
	alpha = data->player_orient;
	delta_alpha = (FOV * M_PI / 180) / WIDTH;
	i = 0;
	while (i < WIDTH && alpha < data->player_orient + (FOV * M_PI / 360) && !i)
	{
		// draw_line(data, alpha, naive_raycaster(data, alpha), 0x0000ff);
		// draw_line(data, alpha, opti_rc(data, alpha, &impact, &wall_orient), 0x0000ff);
		opti_rc(data, alpha, &impact, &wall_orient);
		alpha += delta_alpha;
		++i;
	}
	player = init_image_xpm(data, "assets/textures/perso_minimap.xpm");
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
		player->img_ptr, data->player_x, data->player_y);
	free_img(player);
}

void	build_minimap(t_data *data)
{
	t_img	*wall;
	t_img	*floor;
	int		i;
	int		j;
	int		dim;

	dim = MM_PIXEL;
	wall = init_image(data, dim, dim);
	clear_img(wall, 0xffffff);
	floor = init_image(data, dim, dim);
	i = 0;
	while (i < data->map->max_y && data->map->cube_map[i])
	{
		j = 0;
		while (j < data->map->max_x && data->map->cube_map[i][j] != '\0')
		{
			if (data->map->cube_map[i][j] && data->map->cube_map[i][j] == '1')
			{
				mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
					wall->img_ptr, j * dim, i * dim);
			}
			else
			{
				mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
					floor->img_ptr, j * dim, i * dim);
			}
			++j;
		}
		++i;
	}
	free_img(wall);
	free_img(floor);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:59 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/25 15:32:14 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	in_map(t_data *data, double x, double y)
{
	int	i;
	int	j;

	i = trunc(x) / TEXTURE_DIM;
	j = trunc(y) / TEXTURE_DIM;
	if (i < 0 || i >= data->map->max_x
		|| j < 0 || j >= data->map->max_y)
		return (false);
	return (true);
}

bool	is_wall(t_data *data, double x, double y, char *wall_type)
{
	int	i;
	int	j;

	i = trunc(x) / TEXTURE_DIM;
	j = trunc(y) / TEXTURE_DIM;
	if (in_map(data, x, y) == false)
		return (true);
	if (is_in_charset(data->map->cube_map[j][i],"1234HD"))
	{
		*wall_type = data->map->cube_map[j][i];
		return (true);
	}
	return (false);
}

double	remainder(double value, double modulus)
{
	if (value >= 0.0 && value < modulus)
		return (value);
	while (value < 0.0)
		value += modulus;
	while (value >= modulus)
		value -= modulus;
	return (value);
}

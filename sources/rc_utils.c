/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:59 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/18 12:54:17 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_wall(t_data *data, double x, double y)
{
	int	i;
	int	j;

	i = x / MM_PIXEL;
	j = y / MM_PIXEL;
	if (data->map->cube_map && data->map->cube_map[j]
		&& data->map->cube_map[j][i] && data->map->cube_map[j][i] == '1')
		return (true);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:59 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/17 16:59:07 by smagdela         ###   ########.fr       */
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

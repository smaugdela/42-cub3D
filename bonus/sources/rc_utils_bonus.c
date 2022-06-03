/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:59 by smagdela          #+#    #+#             */
/*   Updated: 2022/06/03 14:55:35 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	in_map(t_data *data, double x, double y)
{
	int	i;
	int	j;

	i = (int)trunc(x) / TEXTURE_DIM;
	j = (int)trunc(y) / TEXTURE_DIM;
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
	if (in_map(data, x, y) && data->map->cube_map[j]
		&& (int)ft_strlen(data->map->cube_map[j]) > i
		&& is_in_charset(data->map->cube_map[j][i], "1234HD "))
	{
		if (wall_type)
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

void	opti_rc_init(t_point *inter_x, t_point *inter_y)
{
	inter_x->x = DBL_MAX;
	inter_x->y = DBL_MAX;
	inter_y->x = DBL_MAX;
	inter_y->y = DBL_MAX;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	char	*tmp_s1;
	char	*tmp_s2;

	tmp_s1 = (char *)s1;
	tmp_s2 = (char *)s2;
	while (ft_strlen(tmp_s1))
	{
		if (*tmp_s1 == '\0' && *tmp_s2 == '\0')
			break ;
		else if (*tmp_s1 != *tmp_s2)
			return (*tmp_s1 - *tmp_s2);
		++tmp_s1;
		++tmp_s2;
	}
	return (0);
}

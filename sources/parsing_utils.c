/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:46:35 by ajearuth          #+#    #+#             */
/*   Updated: 2022/06/03 11:39:01 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	tired_of_norm(int spawn)
{
	if (spawn != 1)
		return (error_messages(3));
	return (true);
}

bool	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
		++i;
	}
	return (true);
}

bool	checkint(char *nb)
{
	char	*int_extremum;
	int		i;

	i = 0;
	if (nb[0] == '-')
	{
		int_extremum = "-2147483648";
		i = 1;
	}
	else
		int_extremum = "2147483647";
	if (ft_strlen(nb) >= ft_strlen(int_extremum))
	{
		while (nb[i])
		{
			if (nb[i] > int_extremum[i] || !ft_isdigit(nb[i]))
				return (false);
			++i;
		}
		return (true);
	}
	else
		return (true);
}

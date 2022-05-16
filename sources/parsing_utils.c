/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:46:35 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/16 15:48:47 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

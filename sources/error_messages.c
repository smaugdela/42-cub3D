/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:02:54 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/16 11:21:34 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	error_message(int i)
{
	if (i == 1)
		ft_putstr_fd("\e[0;31mError\nMap must be surrounded by walls\n", 2);
	if (i == 2)
		ft_putstr_fd("\e[0;31mError\nInvalid texture file(s)\n", 2);
	if (i == 3)
		ft_putstr_fd("\e[0;31mError\nInvalid starting position\n", 2);
	if (i == 4)
		ft_putstr_fd("\e[0;31mError\nInvalid instructions\n", 2);
	if (i == 5)
		ft_putstr_fd("\e[0;31mError\nInvalid file\n", 2);
	if (i == 7)
		ft_putstr_fd("\e[0;31mError\nBad argument number\n", 2);
	return (false);
}

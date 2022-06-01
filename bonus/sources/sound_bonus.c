/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:09:32 by ajearuth          #+#    #+#             */
/*   Updated: 2022/06/01 14:47:37 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	play_sound(char *path, int volume)
{
	char	command[500];
	double	calcul;
	char	*str_volume;

	calcul = (double)volume / 100 * 65536;
	ft_bzero(command, 500);
	ft_strlcat(command, "(" "paplay" " --volume ", 500);
	str_volume = ft_itoa((int)calcul);
	ft_strlcat(command, str_volume, 500);
	free(str_volume);
	ft_strlcat(command, " ", 500);
	ft_strlcat(command, path, 500);
	ft_strlcat(command, " &" ") " " > /dev/null 2>&1", 500);
	return (system(command));
}

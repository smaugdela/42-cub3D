/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:09:32 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/31 15:16:53 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	play_sound(char *path, int volume)
{
	char	command[500];
	double	calcul;

	calcul = (double)volume / 100 * 65536;
	ft_bzero(command, 500);
	ft_strlcat(command, "(" "paplay" " --volume ", 500);
	ft_strlcat(command, ft_itoa((int)calcul), 500);
	ft_strlcat(command, " ", 500);
	ft_strlcat(command, path, 500);
	ft_strlcat(command, " &" ") " " > /dev/null 2>&1", 500);
	return (system(command));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:35:44 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/16 11:21:47 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_map	map;
	if (ac == 2)
	{
		map = init_struct_map(av[1]);
	}
	else
	{
		error_message(7);
		return (-1);
	}
	return (0);
}

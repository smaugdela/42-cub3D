/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:57:13 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/21 15:43:53 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	red_cross_handler(t_image *image)
{
	free_n_destroy(image, image->display);
	ft_putstr_fd("Closing...\n\033[0;32mThanks for using fract'ol!\033[0m\n", 1);
	exit(EXIT_SUCCESS);
	return (0);
}

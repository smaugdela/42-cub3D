/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:27:37 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/23 13:42:40 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static void	init_events(t_display *display, t_image *image)
{
	mlx_loop_hook(display->mlx_ptr, &loop_handler, image);
	mlx_hook(display->win_ptr, DestroyNotify, StructureNotifyMask,
		&red_cross_handler, image);
	mlx_hook(display->win_ptr, KeyPress, KeyPressMask, &keys_handler, image);
	mlx_hook(display->win_ptr, ButtonPress, ButtonPressMask,
		&button_handler, image);
	mlx_hook(display->win_ptr, MotionNotify, PointerMotionMask,
		&pointer_handler, image);
}

static t_fractal	init_fractal(t_image *image, t_fractal fractal)
{
	fractal.max_re = 2;
	fractal.min_re = -2;
	fractal.max_im = 2;
	fractal.min_im = -2;
	fractal.max_iter = MAX_ITER;
	fractal.render = TRUE;
	fractal.display_ui = FALSE;
	fractal.image = image;
	image->fractal = fractal;
	return (fractal);
}

int	main(int argc, char **argv)
{
	t_display	*display;
	t_image		*image;
	t_fractal	fractal;

	fractal = check_args(argc, argv);
	display = init_display("fract'ol");
	image = init_image(display);
	fractal = init_fractal(image, fractal);
	init_events(display, image);
	mlx_loop(display->mlx_ptr);
	free_n_destroy(image, display);
	ft_putstr_fd("Stopping...\n\033[0;32mThanks for using fract'ol!\033[0m\n", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:20:38 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/23 19:29:35 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static void	usage(void)
{
	ft_putstr_fd("Usage: ./fractol <name of fractal set> <color mode>", 1);
	ft_putstr_fd(" [(optional) real part of Julia's parameter] ", 1);
	ft_putstr_fd("[(optional) imaginary part of Julia's paramter]\n\n", 1);
	ft_putstr_fd("List of sets:\n - Mandelbrot\n - Julia\n", 1);
	ft_putstr_fd(" - Burning_Ship\n - Multicorn\n\n", 1);
	ft_putstr_fd("Color Modes:\n - BnW or Grayscale: W/S\n - Red, Green ", 1);
	ft_putstr_fd("or Blue: R/G/B\n - Spectrum, Lagoon or Flame: P/L/F\n\n", 1);
	ft_putstr_fd("Real and imaginary parts should be formated as doubles.", 1);
	ft_putstr_fd(" If given, both real and imaginary part should be, not", 1);
	ft_putstr_fd(" only one. Both should not be above ±2.0.", 1);
	ft_putstr_fd("\n\nExample:    ./fractol Julia P -0.5 -0.1\n\n", 1);
	exit (42);
}

void	*fract_sets(char *set)
{
	if (!ft_strncmp(set, "Mandelbrot", max(ft_strlen(set), 10)))
		return (&draw_mandelbrot);
	else if (!ft_strncmp(set, "Julia", max(ft_strlen(set), 5)))
		return (&draw_julia);
	else if (!ft_strncmp(set, "Burning_Ship", max(ft_strlen(set), 12)))
		return (&draw_ship);
	else if (!ft_strncmp(set, "Multicorn", max(ft_strlen(set), 9)))
		return (&draw_multicorn);
	else
	{
		usage();
		return (NULL);
	}
}

void	*color_sets(char color)
{
	if (color == 'W' || color == 'w')
		return (&color_bnw);
	else if (color == 'S' || color == 's')
		return (&color_grayscale);
	else if (color == 'R' || color == 'r')
		return (&color_r);
	else if (color == 'G' || color == 'g')
		return (&color_g);
	else if (color == 'B' || color == 'b')
		return (&color_b);
	else if (color == 'P' || color == 'p')
		return (&color_multi);
	else if (color == 'L' || color == 'l')
		return (&color_lagoon);
	else if (color == 'F' || color == 'f')
		return (&color_flame);
	else
	{
		usage();
		return (NULL);
	}
}

t_fractal	check_args(int argc, char **argv)
{
	t_fractal	fract;

	if (argc > 5 || argc < 3 || argc == 4)
		usage();
	fract.draw_ft = fract_sets(argv[1]);
	if (ft_strlen(argv[2]) > 1)
		usage();
	fract.color_ft = color_sets(argv[2][0]);
	fract.param.re = 0.0;
	fract.param.im = 0.0;
	if (argc == 5)
	{
		fract.param.re = ft_atof(argv[3]);
		fract.param.im = ft_atof(argv[4]);
		if (fract.param.re > 2 || fract.param.re < -2
			|| fract.param.im > 2 || fract.param.im < -2)
			usage();
	}
	if (fract.param.re == 0 && fract.param.im == 0
		&& fract.draw_ft == &draw_julia)
		ft_putstr_fd("\033[0;35mWARNING:\033[0m default ", 1);
	if (fract.draw_ft == &draw_julia)
		printf("Julia's parameter = %f%+fi\n",
			fract.param.re, fract.param.im);
	return (fract);
}

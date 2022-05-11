/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:26:30 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/23 13:42:40 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

double	complex_magnitude(t_complex z)
{
	return (sqrt(pow(z.re, 2) + pow(z.im, 2)));
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

t_bool	ft_c_in_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (TRUE);
		++charset;
	}
	return (FALSE);
}

t_bool	ft_is_charset(const char *str, char *charset)
{
	int	len;

	len = 0;
	while (ft_c_in_charset(str[len], charset) == TRUE && str[len])
		++len;
	if (str[len] == '\0')
		return (TRUE);
	return (FALSE);
}

double	ft_atof(char *str)
{
	double			result;
	int				i;
	int				sign;
	unsigned int	len;

	i = 0;
	sign = 1;
	result = 0.0;
	if (!ft_is_charset(str, "-+.0123456789") || ft_strlen(str) > 12)
	{
		ft_putstr_fd("ft_atof: invalid input\n", 2);
		return (0.0);
	}
	result = (double)ft_atoi(str);
	while (str[i] && str[i] != '.')
		++i;
	if (str[i] == '.' && str[i + 1])
	{
		++i;
		len = ft_strlen(str) - i;
		result += (double)ft_atoi(str + i) / pow(10, len);
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:47:50 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/26 16:16:28 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(int nb)
{
	unsigned int	len;
	unsigned int	tmp_nb;

	if (nb == 0)
		return (1);
	len = 0;
	if (nb < 0)
	{
		++len;
		tmp_nb = -nb;
	}
	else
		tmp_nb = nb;
	while (tmp_nb)
	{
		++len;
		tmp_nb = tmp_nb / 10;
	}
	return (len);
}

static int	ft_pow(int nb, int power)
{
	if (power == 0)
		return (1);
	else if (power == 1)
		return (nb);
	return (nb * ft_pow(nb, --power));
}

char	*ft_itoa(int n)
{
	char			*str;
	int				tenth_pow;
	int				i;
	unsigned int	tmp_n;

	tenth_pow = ft_nblen(n);
	str = (char *)malloc(tenth_pow + 1);
	if (!str)
		return (NULL);
	i = 0;
	tmp_n = n;
	if (n < 0)
	{
		str[i++] = '-';
		--tenth_pow;
		tmp_n = -n;
	}
	while (tenth_pow--)
	{
		str[i++] = (tmp_n / ft_pow(10, tenth_pow)) + '0';
		tmp_n = tmp_n % ft_pow(10, tenth_pow);
	}
	str[i] = '\0';
	return (str);
}

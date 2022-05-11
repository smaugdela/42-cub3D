/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:23:47 by smagdela          #+#    #+#             */
/*   Updated: 2021/06/02 10:52:52 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp_s;
	unsigned char	tmp_c;

	tmp_c = (unsigned char)c;
	tmp_s = (unsigned char *)s;
	while (n--)
		*(tmp_s++) = tmp_c;
	return (s);
}

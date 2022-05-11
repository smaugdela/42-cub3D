/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:23:26 by smagdela          #+#    #+#             */
/*   Updated: 2021/06/02 10:52:27 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp_src;
	unsigned char	tmp_c;

	tmp_c = (unsigned char)c;
	tmp_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		if (tmp_src[i] == tmp_c)
			return (tmp_src + i);
		++i;
	}
	return (NULL);
}

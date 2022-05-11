/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:23:10 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/21 18:01:54 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp_dest;
	unsigned char	*tmp_src;
	unsigned char	tmp_c;

	tmp_dest = (unsigned char *)dest;
	tmp_src = (unsigned char *)src;
	tmp_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		tmp_dest[i] = tmp_src[i];
		if (tmp_src[i] == tmp_c)
			return (tmp_dest + i + 1);
		++i;
	}
	return (NULL);
}

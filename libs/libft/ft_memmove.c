/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:23:44 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/21 17:55:41 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_dest;
	unsigned char	*tmp_src;

	tmp_src = (unsigned char *)src;
	tmp_dest = (unsigned char *)dest;
	if (dest < src)
		ft_memcpy(dest, src, n);
	else if (dest > src)
	{
		while (n--)
			*(tmp_dest + n) = *(tmp_src + n);
	}
	return (dest);
}

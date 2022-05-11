/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:18:47 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/23 15:45:37 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	if (src == NULL)
		return (0);
	len = ft_strlen(src);
	if (dstsize <= 0)
		return (len);
	i = 0;
	while (--dstsize && src[i])
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (len);
}

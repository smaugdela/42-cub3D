/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:24:10 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/31 12:15:32 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	if (size == 0)
		return (ft_strlen(src));
	len = ft_strlen(dest);
	if (size < len)
		len = size;
	i = 0;
	while ((i + len) < (size - 1) && src[i])
	{
		dest[len + i] = src[i];
		++i;
	}
	if (len < size)
		dest[len + i] = '\0';
	return (len + ft_strlen(src));
}

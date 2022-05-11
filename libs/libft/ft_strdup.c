/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:24:07 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/25 11:27:59 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dest;
	size_t	i;

	dest = (char *)malloc(ft_strlen(str) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (*(str + i))
	{
		*(dest + i) = *(str + i);
		++i;
	}
	*(dest + i) = '\0';
	return (dest);
}

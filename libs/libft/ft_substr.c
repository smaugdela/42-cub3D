/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:08:52 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/31 15:57:57 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (!s)
		return (NULL);
	subs = (char *)malloc((ft_min(len, ft_strlen(s)) + 1) * sizeof(char));
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len && (start + i) < ft_strlen(s))
	{
		subs[i] = s[start + i];
		++i;
	}
	subs[i] = '\0';
	return (subs);
}

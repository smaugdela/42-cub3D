/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:24:47 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/25 11:45:15 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*big_s;
	unsigned int	i;
	unsigned int	j;

	if ((s1 == NULL || s2 == NULL))
		return (NULL);
	big_s = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!big_s)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		big_s[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		big_s[i + j] = s2[j];
		++j;
	}
	big_s[i + j] = '\0';
	return (big_s);
}

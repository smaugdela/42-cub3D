/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:48:04 by smagdela          #+#    #+#             */
/*   Updated: 2022/05/17 18:46:26 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(const char *set, const char c)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		++i;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set, const char *sep)
{
	unsigned int	start;
	int				i;

	if (s1 == NULL || set == NULL || sep == NULL)
		return (NULL);
	start = 0;
	while ((ft_isinset(set, s1[start]) || ft_isinset(sep, s1[start]))
		&& s1[start])
		++start;
	i = ft_strlen(s1) - 1;
	while ((ft_isinset(set, s1[i]) || ft_isinset(sep, s1[i]))
		&& s1[start] && i >= 0)
		--i;
	return (ft_substr(s1, start, ++i - start));
}

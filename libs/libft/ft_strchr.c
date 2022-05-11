/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:23:58 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/31 12:06:20 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned int	len;
	char			tmp_c;

	tmp_c = (char)c;
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (*(s + i) == tmp_c)
			return ((char *)(s + i));
		++i;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:27:29 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/31 12:08:58 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	len;
	char			tmp_c;

	tmp_c = (char)c;
	len = ft_strlen(s);
	while (len + 1)
	{
		if (*(s + len) == tmp_c)
			return ((char *)(s + len));
		--len;
	}
	return (NULL);
}

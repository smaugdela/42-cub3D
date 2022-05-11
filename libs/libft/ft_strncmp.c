/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:44:58 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/23 15:07:10 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	while (n--)
	{
		if (*tmp_s1 == '\0' && *tmp_s2 == '\0')
			break ;
		else if (*tmp_s1 != *tmp_s2)
			return (*tmp_s1 - *tmp_s2);
		++tmp_s1;
		++tmp_s2;
	}
	return (0);
}

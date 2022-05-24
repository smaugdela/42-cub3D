/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 09:18:13 by ajearuth          #+#    #+#             */
/*   Updated: 2022/05/13 11:49:24 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

char	*ft_strndup(char *str, int n)
{
	char	*result;
	int		i;

	if (str == NULL)
		i = 0;
	else
		i = ft_strlen_gnl(str);
	if (i < n || n < 0)
		n = i;
	result = malloc(sizeof(char) * (n + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < n && str[i] != '\n')
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}

int	ft_find_end(const char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

char	*ft_next_buffer(char *new_buffer, char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		new_buffer[i] = buffer[i];
		++i;
	}
	return (new_buffer);
}

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*p;
	char	*res;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strndup(s2, -1));
	if (s2 == NULL)
		return (ft_strndup(s1, -1));
	res = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (res == NULL)
		return (NULL);
	p = res;
	while (*s1)
		*p++ = *s1++;
	while (*s2 && n && *s2 != '\n')
	{
		--n;
		*p++ = *s2++;
	}
	*p = '\0';
	return (res);
}

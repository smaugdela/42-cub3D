/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 09:22:16 by ajearuth          #+#    #+#             */
/*   Updated: 2022/01/07 16:13:28 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_dupline(char **line, char *buffer)
{	
	char	*tmp_line;

	tmp_line = ft_strnjoin(*line, buffer, ft_strlen_gnl(buffer));
	if (tmp_line == NULL)
		return (-1);
	free(*line);
	*line = ft_strndup(tmp_line, -1);
	free(tmp_line);
	if (line == NULL)
		return (-1);
	return (1);
}

static int	ft_ret(char **line, char *buffer, int ret_buffer)
{
	int	i;
	int	index;

	if (ret_buffer == -1)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	if (ft_find_end(buffer, '\n') == -1)
	{
		ft_dupline(line, buffer);
		buffer[0] = '\0';
		return (0);
	}
	else
	{
		ft_dupline(line, buffer);
		i = -1;
		index = ft_find_end(buffer, '\n');
		while (buffer[index + ++i + 1])
			buffer[i] = buffer[index + i + 1];
		buffer[i] = '\0';
		return (1);
	}
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			ret_buffer;

	*line = NULL;
	if (BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (ft_strlen_gnl(buffer) == 0)
	{
		ret_buffer = read(fd, buffer, BUFFER_SIZE);
		buffer[ret_buffer] = '\0';
		*line = NULL;
	}	
	else
		ret_buffer = BUFFER_SIZE;
	while (ret_buffer == BUFFER_SIZE && ft_find_end(buffer, '\n') == -1)
	{
		ft_dupline(line, buffer);
		ret_buffer = read(fd, buffer, BUFFER_SIZE);
		buffer[ret_buffer] = '\0';
	}
	return (ft_ret(line, buffer, ret_buffer));
}

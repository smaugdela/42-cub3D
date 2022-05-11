/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 15:38:12 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/27 16:56:10 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*tmp_lst;

	if (lst == NULL)
		return (0);
	size = 1;
	tmp_lst = lst;
	while (tmp_lst->next)
	{
		++size;
		tmp_lst = tmp_lst -> next;
	}
	return (size);
}

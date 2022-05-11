/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:20:39 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/27 16:51:07 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp_lst;

	if (lst != NULL && del != NULL)
	{
		while (*lst != NULL)
		{
			tmp_lst = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp_lst;
		}
		lst = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 15:55:21 by smagdela          #+#    #+#             */
/*   Updated: 2021/05/27 16:15:59 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp_lst;

	if (alst != NULL && *alst != NULL)
	{
		tmp_lst = ft_lstlast(*alst);
		tmp_lst -> next = new;
	}
	else
		*alst = new;
}

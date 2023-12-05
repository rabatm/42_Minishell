/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchauvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:14:33 by hchauvin          #+#    #+#             */
/*   Updated: 2023/05/15 12:15:56 by hchauvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*strt;

	if (!lst || !*lst)
		return ;
	while (*lst != 0)
	{
		strt = (*lst)->next;
		ft_lstdelone((*lst), del);
		(*lst) = strt;
	}
}

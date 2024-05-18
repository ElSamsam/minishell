/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 23:04:00 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/21 18:31:58 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*temp;

	first = (t_list *)malloc(sizeof(t_list));
	if (!first || !lst || !f || !del)
		return (NULL);
	first->content = f(lst->content);
	temp = first;
	while (lst->next)
	{
		temp->next = (t_list *)malloc(sizeof(t_list));
		if (!temp->next)
			return (ft_lstclear(&first, del), NULL);
		temp = temp->next;
		lst = lst->next;
		temp->content = f(lst->content);
	}
	temp->next = NULL;
	return (first);
}

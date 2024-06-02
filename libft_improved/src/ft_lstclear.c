/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:00:04 by saperrie          #+#    #+#             */
/*   Updated: 2023/11/21 18:30:12 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!*lst || !lst || !del)
		return ;
	if ((*lst)->next)
	{
		ft_lstclear(&(*lst)->next, del);
	}
	del((*lst)->content);
	free(*lst);
	*lst = NULL;
}

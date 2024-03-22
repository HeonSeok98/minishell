/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:16:05 by dna               #+#    #+#             */
/*   Updated: 2023/10/28 21:19:45 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr_lst;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		ptr_lst = *lst;
		while (ptr_lst->next)
			ptr_lst = ptr_lst->next;
		ptr_lst->next = new;
	}
}

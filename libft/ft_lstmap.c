/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:19:46 by dna               #+#    #+#             */
/*   Updated: 2023/11/04 10:13:26 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	void	*tmp_f;
	t_list	*tmp;

	ptr = NULL;
	while (lst)
	{
		tmp_f = f(lst->content);
		tmp = ft_lstnew(tmp_f);
		if (!tmp)
		{
			del(tmp_f);
			ft_lstclear(&ptr, del);
			return (NULL);
		}
		else
		{
			ft_lstadd_back(&ptr, tmp);
			tmp = tmp->next;
			lst = lst->next;
		}
	}
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:13:13 by dna               #+#    #+#             */
/*   Updated: 2023/10/21 10:35:28 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *) malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	else
	{
		ptr->content = content;
		ptr->next = NULL;
		return (ptr);
	}
}

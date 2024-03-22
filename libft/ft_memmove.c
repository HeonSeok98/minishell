/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:11:11 by dna               #+#    #+#             */
/*   Updated: 2023/11/05 14:42:15 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;

	ptr_dst = (unsigned char *) dst;
	ptr_src = (unsigned char *) src;
	if (ptr_dst == ptr_src)
		return (dst);
	else if (ptr_dst > ptr_src)
	{
		ptr_dst += len;
		ptr_src += len;
		while (len--)
			*--ptr_dst = *--ptr_src;
	}
	else
		while (len--)
			*ptr_dst++ = *ptr_src++;
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:06:38 by dna               #+#    #+#             */
/*   Updated: 2023/10/28 21:04:58 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;

	ptr_dst = (unsigned char *) dst;
	ptr_src = (const unsigned char *) src;
	if (ptr_dst == ptr_src)
		return (dst);
	else
	{
		while (n--)
			*ptr_dst++ = *ptr_src++;
		return (dst);
	}
}

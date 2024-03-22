/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:19:37 by dna               #+#    #+#             */
/*   Updated: 2023/10/28 21:20:16 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr_s;
	unsigned char		uchar_c;

	ptr_s = (const unsigned char *) s;
	uchar_c = (unsigned char) c;
	while (n--)
	{
		if (*ptr_s == uchar_c)
			return ((void *) ptr_s);
		else
			++ptr_s;
	}
	return (NULL);
}

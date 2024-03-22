/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:00:02 by dna               #+#    #+#             */
/*   Updated: 2023/10/15 13:55:28 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr_b;
	unsigned char	uchar_c;

	ptr_b = (unsigned char *) b;
	uchar_c = (unsigned char) c;
	while (len--)
		*ptr_b++ = uchar_c;
	return (b);
}

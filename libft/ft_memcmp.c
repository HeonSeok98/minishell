/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:26:42 by dna               #+#    #+#             */
/*   Updated: 2023/10/28 21:05:03 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr_s1;
	const unsigned char	*ptr_s2;

	ptr_s1 = (const unsigned char *) s1;
	ptr_s2 = (const unsigned char *) s2;
	while (n--)
	{
		if (*ptr_s1 != *ptr_s2)
			return (*ptr_s1 - *ptr_s2);
		else
		{
			++ptr_s1;
			++ptr_s2;
		}
	}
	return (0);
}

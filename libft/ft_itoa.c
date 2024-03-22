/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:25:41 by dna               #+#    #+#             */
/*   Updated: 2023/10/28 20:13:03 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	len;

	len = 0;
	if (n < 1)
		++len;
	while (n)
	{
		++len;
		n /= 10;
	}
	return (len);
}

static long long	ft_abs(long long n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

char	*ft_itoa(int n)
{
	size_t		n_len;
	long long	ll_n;
	char		*ptr;
	char		*rev_ptr;

	n_len = ft_intlen(n);
	ptr = (char *) malloc((n_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	else
	{
		ll_n = ft_abs((long long) n);
		rev_ptr = ptr + n_len;
		*rev_ptr = '\0';
		if (n == 0)
			*ptr = '0';
		while (ll_n)
		{
			*--rev_ptr = ll_n % 10 + '0';
			ll_n /= 10;
		}
		if (n < 0)
			*ptr = '-';
		return (ptr);
	}
}

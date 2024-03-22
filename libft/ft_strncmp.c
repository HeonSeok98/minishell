/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:27:58 by dna               #+#    #+#             */
/*   Updated: 2023/10/21 11:00:23 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*ptr_s1;
	const unsigned char	*ptr_s2;

	ptr_s1 = (const unsigned char *) s1;
	ptr_s2 = (const unsigned char *) s2;
	while (*ptr_s1 && *ptr_s2 && n)
	{
		if (*ptr_s1 != *ptr_s2)
			return (*ptr_s1 - *ptr_s2);
		else
		{
			++ptr_s1;
			++ptr_s2;
			--n;
		}
	}
	if (n != 0)
		return (*ptr_s1 - *ptr_s2);
	else
		return (0);
}

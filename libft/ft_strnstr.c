/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:38:10 by dna               #+#    #+#             */
/*   Updated: 2023/11/05 14:42:06 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (*needle)
	{
		while (*haystack && len)
		{
			i = 0;
			while (i < len && *(haystack + i) == *(needle + i))
				if (*(needle + ++i) == '\0')
					return ((char *) haystack);
			if (i < len--)
				++haystack;
			else
				return (NULL);
		}
		return (NULL);
	}
	else
		return ((char *) haystack);
}

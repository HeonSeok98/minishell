/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:03:53 by dna               #+#    #+#             */
/*   Updated: 2023/10/21 13:25:22 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *) malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	else
	{
		while (*s1)
			*ptr++ = *s1++;
		while (*s2)
			*ptr++ = *s2++;
		*ptr = '\0';
		return (ptr - s1_len - s2_len);
	}
}

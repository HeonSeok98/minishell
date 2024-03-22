/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:54:33 by dna               #+#    #+#             */
/*   Updated: 2023/11/04 09:34:37 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*ptr;
	size_t	i;

	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	else
	{
		if (start + len > s_len)
			len = s_len - start;
		ptr = (char *) malloc((len + 1) * sizeof(char));
		if (!ptr)
			return (NULL);
		else
		{
			s += start;
			i = 0;
			while (i++ < len && *s)
				*ptr++ = *s++;
			*ptr = '\0';
			return (ptr - --i);
		}
	}
}

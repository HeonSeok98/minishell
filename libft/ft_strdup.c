/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:45:05 by dna               #+#    #+#             */
/*   Updated: 2023/11/04 12:25:48 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s1_len;
	char	*dup;

	s1_len = ft_strlen(s1);
	dup = (char *) malloc(++s1_len * sizeof(char));
	if (!dup)
		return (NULL);
	else
	{
		ft_memcpy(dup, s1, s1_len);
		return (dup);
	}
}

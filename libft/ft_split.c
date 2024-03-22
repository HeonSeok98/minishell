/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:20:42 by dna               #+#    #+#             */
/*   Updated: 2024/01/12 10:20:10 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static size_t	ft_splitcount(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			++count;
		++s;
	}
	return (count);
}

static size_t	ft_splitsize(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (*s && *s++ != c)
		++size;
	return (size);
}

static char	**ft_splitfree(char **ptr, int i)
{
	if (!*(ptr + i))
	{
		while (i > -1)
			free(*(ptr + i--));
		free(ptr);
		ptr = NULL;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	count;
	size_t	i;
	size_t	splitsize;

	count = ft_splitcount(s, c);
	ptr = (char **) malloc((count + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	else
	{
		i = 0;
		while (i < count)
		{
			while (*s == c)
				++s;
			splitsize = ft_splitsize(s, c);
			*(ptr + i) = ft_substr(s, 0, splitsize);
			if (!ft_splitfree(ptr, i++))
				return (NULL);
			s += splitsize;
		}
		*(ptr + i) = NULL;
		return (ptr);
	}
}

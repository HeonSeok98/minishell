/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:16:14 by dna               #+#    #+#             */
/*   Updated: 2023/11/11 12:28:17 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	char	*ptr;

	begin = 0;
	while (*(s1 + begin) && ft_strchr(set, *(s1 + begin)))
		++begin;
	end = ft_strlen(s1);
	while (end > begin && ft_strchr(set, *(s1 + end - 1)))
		--end;
	ptr = malloc(end - begin + 1);
	if (!ptr)
		return (NULL);
	else
	{
		ft_strlcpy(ptr, s1 + begin, end - begin + 1);
		return (ptr);
	}
}

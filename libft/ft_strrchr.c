/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:20:00 by dna               #+#    #+#             */
/*   Updated: 2023/10/21 10:19:34 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	char_c;
	char	*ptr;

	char_c = (char) c;
	ptr = NULL;
	while (*s)
	{
		if (*s == char_c)
			ptr = (char *) s;
		++s;
	}
	if (char_c == '\0')
		ptr = (char *) s;
	return (ptr);
}

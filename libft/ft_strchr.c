/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:01:54 by dna               #+#    #+#             */
/*   Updated: 2023/10/21 10:00:50 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	char_c;

	char_c = (char) c;
	while (*s)
	{
		if (*s == char_c)
			return ((char *) s);
		else
			++s;
	}
	if (char_c == '\0')
		return ((char *) s);
	else
		return (NULL);
}

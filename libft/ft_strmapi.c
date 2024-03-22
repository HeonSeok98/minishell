/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:06:43 by dna               #+#    #+#             */
/*   Updated: 2023/10/28 17:07:29 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	i;

	ptr = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	else
	{
		i = 0;
		while (*s)
			*ptr++ = f(i++, *s++);
		*ptr = '\0';
		return (ptr - i);
	}
}

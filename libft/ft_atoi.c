/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:07:53 by dna               #+#    #+#             */
/*   Updated: 2023/10/28 19:18:53 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strsign(const char **str, int *sign)
{
	if (**str == '+' || **str == '-')
	{
		if (**str == '+')
			*sign = 1;
		else
			*sign = -1;
		++*str;
	}
}

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	value;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		++str;
	sign = 1;
	ft_strsign(&str, &sign);
	value = 0;
	while (*str >= '0' && *str <= '9')
	{
		value *= 10;
		value += (*str - '0');
		++str;
	}
	return (sign * value);
}

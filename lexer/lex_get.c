/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:21:51 by dna               #+#    #+#             */
/*   Updated: 2024/02/22 17:21:51 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	isdollar(char *token, int i)
{
	if (*(token + i) != ' ' && *(token + i) != '$')
		return (1);
	else
		return (0);
}

void	cat_getin(t_node **lst, char *token, size_t size, ssize_t cat)
{
	size_t	i;
	size_t	j;
	char	quote;
	char	*data;

	i = 0;
	j = 0;
	data = ft_calloc(size - 2 * cat + 1, sizeof(char));
	while (i < size)
	{
		if (*(token + i) == '\'' || *(token + i) == '\"')
		{
			quote = *(token + i);
			if (cat < 1)
				*(data + j++) = quote;
			while (*(token + ++i) && *(token + i) != quote)
				*(data + j++) = *(token + i);
			--cat;
		}
		else
			*(data + j++) = *(token + i);
		++i;
	}
	node_add_back(lst, node_init(data, WRITE));
}

void	cat_getout(t_node **lst, char *token, size_t size, ssize_t cat)
{
	size_t	i;
	size_t	j;
	char	quote;
	char	*data;

	i = 0;
	j = 0;
	data = ft_calloc(size - 2 * cat + 1, sizeof(char));
	while (i < size)
	{
		if (*(token + i) == '\'' || *(token + i) == '\"')
		{
			quote = *(token + i);
			while (*(token + ++i) && *(token + i) != quote)
				*(data + j++) = *(token + i);
		}
		else
			*(data + j++) = *(token + i);
		++i;
	}
	node_add_back(lst, node_init(data, WRITE));
}

void	lex_get(t_node **lst, char *token, size_t size)
{
	size_t	i;
	char	quote;
	ssize_t	cat;

	i = 0;
	cat = 0;
	while (i < size)
	{
		if (*(token + i) == '\'' || *(token + i) == '\"')
		{
			quote = *(token + i);
			while (*(token + ++i) && *(token + i) != quote)
				;
			if (*(token + i) != quote)
			{
				cat_getin(lst, token, size, cat);
				return ;
			}
			else
				++cat;
		}
		++i;
	}
	cat_getout(lst, token, size, cat);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_put_to.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:21:24 by dna               #+#    #+#             */
/*   Updated: 2024/02/22 17:21:26 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cat_put_toin(t_node **lst, char *token, size_t size, ssize_t cat)
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
	node_add_back(lst, node_init(data, HERE_DOC));
}

void	cat_put_toout(t_node **lst, char *token, size_t size, ssize_t cat)
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
	node_add_back(lst, node_init(data, HERE_DOC));
}

void	lex_put_to(t_node **lst, char *token, size_t size)
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
				cat_put_toin(lst, token, size, cat);
				return ;
			}
			else
				++cat;
		}
		++i;
	}
	cat_put_toout(lst, token, size, cat);
}

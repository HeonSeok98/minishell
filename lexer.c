/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:01:32 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:09:13 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*node_init(char *data, int type)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	else
	{
		node->data = data;
		node->type = type;
		node->prev = NULL;
		node->next = NULL;
	}
	return (node);
}

void	node_add_back(t_node **lst, t_node *node)
{
	t_node	*tmp;

	if (node)
	{
		if (!*lst)
			*lst = node;
		else
		{
			tmp = *lst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = node;
			node->prev = tmp;
		}
	}
}

void	syntax_free(char *s, t_node *node)
{
	free(node);
	syntax_error(s);
}

ssize_t	lexer_command(t_envp *envport, t_node **lst, char **token, ssize_t i)
{
	ssize_t	count;
	size_t	size;
	int		j;
	int		k;

	j = 0;
	k = 0;
	count = token_count(*(token + i), " \t");
	*(token + i) = for_dollar(*(token + i), envport);
	while (j < count)
	{
		size = token_size(*(token + i) + k, " \t", 0);
		if (ft_memcmp(token[i] + k, " ", 1) && ft_memcmp(token[i] + k, "\t", 1))
			quotesize(lst, *(token + i) + k, size);
		k += size;
		++j;
	}
	return (++i);
}

t_node	*lexer(char **token, t_envp *envport, ssize_t i)
{
	t_node	*lexical;

	lexical = NULL;
	while (*(token + i) && i != -1)
	{
		if (*token[i] == '|' || *token[i] == '&')
			i = lexer_pipe(&lexical, token, i);
		else if (token[i + 1] && *token[i + 1] == '<' && *token[i] == '<')
			i = lexer_put_to(envport, &lexical, token, i);
		else if (*token[i] == '(' || *token[i] == '<')
			i = lexer_put(envport, &lexical, token, i);
		else if (token[i + 1] && *token[i + 1] == '>' && *token[i] == '>')
			i = lexer_get_from(envport, &lexical, token, i);
		else if (*token[i] == ')' || *token[i] == '>')
			i = lexer_get(envport, &lexical, token, i);
		else
			i = lexer_command(envport, &lexical, token, i);
	}
	if (i != -1)
		return (lexical);
	frexer(lexical);
	return (NULL);
}

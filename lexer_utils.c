/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:45:13 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:09:15 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	lexer_pipe(t_node **lst, char **token, ssize_t i)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		return (-1);
	else if (**(token + i) == '&')
	{
		syntax_free("syntax error near unexpected token `&'\n", node);
		return (-1);
	}
	else if (!*(token + i + 1) || **(token + i + 1) == '|')
	{
		syntax_free("syntax error near unexpected token `|'\n", node);
		return (-1);
	}
	else
	{
		node->data = ft_strdup("|");
		node->type = PIPE;
		node->prev = NULL;
		node->next = NULL;
		node_add_back(lst, node);
		i += 1;
		return (i);
	}
}

ssize_t	lexer_put_to(t_envp *envport, t_node **lst, char **token, ssize_t i)
{
	if (!*(token + i + 2))
	{
		syntax_error("syntax error near unexpected token `newline\'\n");
		return (-1);
	}
	else if (**(token + i + 2) == '<')
	{
		syntax_error("syntax error near unexpected token `<'\n");
		return (-1);
	}
	lexeredirects(envport, lst, token, i);
	i += 3;
	return (i);
}

ssize_t	lexer_put(t_envp *envport, t_node **lst, char **token, ssize_t i)
{
	if (**(token + i) == '(')
	{
		syntax_error("syntax error near unexpected token `(\'\n");
		return (-1);
	}
	else if (!*(token + i + 1))
	{
		syntax_error("syntax error near unexpected token `newline\'\n");
		return (-1);
	}
	lexeredirect(envport, lst, token, i);
	i += 2;
	return (i);
}

ssize_t	lexer_get_from(t_envp *envport, t_node **lst, char **token, ssize_t i)
{
	if (!*(token + i + 2))
	{
		syntax_error("syntax error near unexpected token `newline\'\n");
		return (-1);
	}
	else if (**(token + i + 2) == '>')
	{
		syntax_error("syntax error near unexpected token `>'\n");
		return (-1);
	}
	lexeredirects(envport, lst, token, i);
	i += 3;
	return (i);
}

ssize_t	lexer_get(t_envp *envport, t_node **lst, char **token, ssize_t i)
{
	if (**(token + i) == ')')
	{
		syntax_error("syntax error near unexpected token `)\'\n");
		return (-1);
	}
	else if (!*(token + i + 1))
	{
		syntax_error("syntax error near unexpected token `newline\'\n");
		return (-1);
	}
	lexeredirect(envport, lst, token, i);
	i += 2;
	return (i);
}

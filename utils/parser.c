/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:46:29 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:09:22 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_free(t_node **lst)
{
	t_node	*now;
	t_node	*tmp;

	if (!lst)
		return ;
	now = *lst;
	while (now)
	{
		tmp = now->next;
		free(now->data);
		free(now);
		now = tmp;
	}
	*lst = NULL;
}

void	order_arr2(t_node **new, t_node *now, char **tmp1, char **tmp2)
{
	char	*tmp3;

	if (now->type == COMMAND)
	{
		*tmp2 = ft_strjoin(*tmp1, " ");
		free(*tmp1);
		tmp3 = ft_strdup(now->data);
		*tmp1 = ft_strjoin(*tmp2, tmp3);
		free(*tmp2);
		free(tmp3);
	}
	else
		node_add_back(new, node_init(ft_strdup(now->data), now->type));
}

int	order_arr3(t_node **new, char **tmp1, int cmd)
{
	cmd++;
	node_add_back(new, node_init(*tmp1, COMMAND));
	*tmp1 = ft_strdup(" ");
	node_add_back(new, node_init(ft_strdup("|"), PIPE));
	return (cmd);
}

void	parser(t_node **node, t_envp **envport)
{
	t_node	*new;
	t_node	*now;
	char	*tmp1;
	char	*tmp2;
	int		cmd;

	now = *node;
	cmd = 0;
	new = NULL;
	tmp1 = ft_strdup(" ");
	while (now)
	{
		if (now->type == PIPE)
			cmd = order_arr3(&new, &tmp1, cmd);
		else
			order_arr2(&new, now, &tmp1, &tmp2);
		now = now->next;
	}
	node_add_back(&new, node_init(tmp1, COMMAND));
	node_free(node);
	execute_arr(&new, envport, cmd);
	node_free(&new);
}

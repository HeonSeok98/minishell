/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:08:30 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:08:33 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset2(t_envp *now, char *cmd)
{
	t_envp	*tmp;

	if (!ft_strcmp(now->name, cmd))
	{
		tmp = now;
		now = now->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	else
		now = now->next;
}

void	builtin_unset(t_node *node, t_envp **envport)
{
	int		i;
	char	**cmd_arr;
	t_envp	*now;

	i = 1;
	cmd_arr = ft_split(node->data, ' ');
	while (cmd_arr[i])
	{
		now = *envport;
		while (now)
		{
			builtin_unset2(now, cmd_arr[i]);
			now = now->next;
		}
		i++;
	}
	arr_free(cmd_arr);
}

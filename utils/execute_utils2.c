/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:47:02 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 16:47:04 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_node **node, t_envp **envport)
{
	if (!ft_strncmp((*node)->data, "  export ", 9) && !((*node)->next))
		export_add(*node, envport);
	else if (!ft_strncmp((*node)->data, "  unset ", 8) && !((*node)->next))
		builtin_unset(*node, envport);
	else if (!ft_strcmp((*node)->data, "  unset") && !((*node)->next))
		;
	else if (!ft_strncmp((*node)->data, "  cd ", 5) && !((*node)->next))
		change_directory((*node)->data, envport);
	else if (!ft_strcmp((*node)->data, "  cd") && !((*node)->next))
		return (1);
	else if (!ft_strncmp((*node)->data, "  exit ", 7) && !((*node)->next))
		builtin_exit(*node, envport);
	else if (!ft_strcmp((*node)->data, "  exit") && !((*node)->next))
		builtin_exit(*node, envport);
	else
		return (0);
	return (1);
}

void	check_hd_name(t_node *now, t_envp **envport)
{
	char	*hd_name;
	char	*num;
	int		hd_num;
	int		here_doc_fd;

	hd_num = 0;
	hd_num++;
	num = ft_itoa(hd_num);
	hd_name = ft_strjoin("tmp", num);
	while (access(hd_name, 0) != -1)
	{
		free(hd_name);
		free(num);
		hd_num++;
		num = ft_itoa(hd_num);
		hd_name = ft_strjoin("tmp", num);
	}
	now->type += hd_num;
	free(num);
	here_doc_fd = open(hd_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	here_doc_read(here_doc_fd, now->data, envport, 255);
	free(hd_name);
}

void	make_tmp(t_node **node, t_envp **envport)
{
	t_node	*now;

	now = *node;
	while (now)
	{
		if (now->type == HERE_DOC)
		{
			check_hd_name(now, envport);
		}
		now = now->next;
	}
}

void	unlink_tmp(t_node **node)
{
	int		hd_num;
	char	*hd_name;
	char	*num;
	t_node	*now;

	now = *node;
	while (now)
	{
		if (now->type >= HERE_DOC)
		{
			hd_num = now->type - 10;
			num = ft_itoa(hd_num);
			hd_name = ft_strjoin("tmp", num);
			unlink(hd_name);
			free(num);
			free(hd_name);
		}
		now = now->next;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

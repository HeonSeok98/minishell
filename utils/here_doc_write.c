/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:37:14 by dna               #+#    #+#             */
/*   Updated: 2024/02/22 15:37:22 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_write3(int here_doc_fd, char *env_str, t_envp **envport)
{
	t_envp	*now;

	now = *envport;
	while (now)
	{
		if (!ft_strcmp(now->name, env_str))
		{
			write(here_doc_fd, now->value, ft_strlen(now->value));
			break ;
		}
		now = now->next;
	}
}

void	here_doc_write2(int here_doc_fd, char *line, int *i, t_envp **envport)
{
	char	*env_str;
	int		j;
	int		k;

	(*i)++;
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0' && line[*i] != '$')
		(*i)++;
	env_str = (char *)malloc(*i - j + 1);
	if (!env_str)
		return ;
	env_str[*i - j] = '\0';
	k = 0;
	while (j != *i)
	{
		env_str[k] = line[j];
		j++;
		k++;
	}
	here_doc_write3(here_doc_fd, env_str, envport);
	(*i)--;
	free(env_str);
}

void	here_doc_write(int here_doc_fd, char *line, t_envp **envport)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '$')
			write(here_doc_fd, &line[i], 1);
		else if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '))
			write(here_doc_fd, &line[i], 1);
		else
			here_doc_write2(here_doc_fd, line, &i, envport);
		i++;
	}
	write(here_doc_fd, "\n", 1);
}

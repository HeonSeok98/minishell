/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:07:11 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:08:46 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envport_len(t_envp **envport)
{
	int		i;
	t_envp	*now;

	if (!*envport)
		return (0);
	i = 0;
	now = *envport;
	while (now)
	{
		i++;
		now = now->next;
	}
	return (i);
}

char	**make_envp(t_envp **envport)
{
	int		i;
	int		l;
	char	**envp;
	t_envp	*now;
	char	*tmp;

	l = envport_len(envport);
	envp = (char **)malloc((l + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	envp[l] = NULL;
	i = 0;
	now = *envport;
	while (now)
	{
		tmp = ft_strjoin(now->name, "=");
		envp[i] = ft_strjoin(tmp, now->value);
		free(tmp);
		now = now->next;
		i++;
	}
	return (envp);
}

void	envp_add_back(t_envp **envport, t_envp *new)
{
	t_envp	*now;

	if (*envport == NULL)
	{
		*envport = new;
		return ;
	}
	now = *envport;
	while (now->next)
		now = now->next;
	now->next = new;
	new->prev = now;
}

char	*find_envport(char *token, t_envp *envport, char *target, size_t *i)
{
	size_t	bytes;
	char	*value;

	if (!ft_strlen(target))
	{
		free(target);
		if (*(token + *i) == '?')
			target = strdup2go(i);
		else
			return (ft_strdup("$"));
	}
	bytes = ft_strlen(target) + 1;
	while (envport)
	{
		if (!ft_memcmp(envport->name, target, bytes))
		{
			value = ft_strdup(envport->value);
			free(target);
			return (value);
		}
		envport = envport->next;
	}
	value = ft_strdup(" ");
	free(target);
	return (value);
}

void	envport_free(t_envp **envport)
{
	t_envp	*now;
	t_envp	*tmp;

	if (!envport)
		return ;
	now = *envport;
	while (now)
	{
		tmp = now->next;
		free(now->name);
		free(now->value);
		free(now);
		now = tmp;
	}
	*envport = NULL;
}

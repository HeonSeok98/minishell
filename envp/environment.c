/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:41:51 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:08:38 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] != '=')
		i++;
	name = (char *) malloc((i + 1) * sizeof(char));
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*find_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '=' && j == 0)
			j = i;
		i++;
	}
	value = (char *) malloc((i - j + 1) * sizeof(char));
	if (!value)
		return (NULL);
	i = 0;
	j++;
	while (str[j])
	{
		value[i] = str[j];
		i++;
		j++;
	}
	value[i] = '\0';
	return (value);
}

t_envp	*new_envp(char *envp)
{
	t_envp	*new;

	new = (t_envp *) malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	else
	{
		new->name = find_name(envp);
		new->value = find_value(envp);
		new->printed = 0;
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
}

void	envp_init(t_envp **envport, char *envp[])
{
	int		i;
	t_envp	*new;

	i = 0;
	new = new_envp("?=0");
	envp_add_back(envport, new);
	while (envp[i])
	{
		new = new_envp(envp[i]);
		envp_add_back(envport, new);
		i++;
	}
	if (!find_envp(envport, "OLDPWD"))
	{
		new = extra_envp("OLDPWD");
		new->value = ft_strdup("");
		envp_add_back(envport, new);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dna <dna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:07:40 by dna               #+#    #+#             */
/*   Updated: 2024/02/20 10:07:44 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*find_envp(t_envp **envport, char *name)
{
	t_envp	*now;

	now = *envport;
	while (now)
	{
		if (!ft_strcmp(now->name, name))
			return (now);
		now = now->next;
	}
	return (NULL);
}

void	change_oldpwd(t_envp **envport)
{
	t_envp	*now;
	char	*tmp1;

	now = find_envp(envport, "PWD");
	if (!now)
		return ;
	else
	{
		tmp1 = now->value;
		now = find_envp(envport, "OLDPWD");
		if (now)
		{
			free(now->value);
			now->value = tmp1;
		}
	}
}

void	change_pwd(t_envp **envport)
{
	t_envp	*now;
	char	*tmp3;
	char	*tmp4;
	char	new_pwd[1024];

	getcwd(new_pwd, sizeof(new_pwd));
	tmp3 = ft_strdup(new_pwd);
	tmp4 = ft_strjoin("PWD=", new_pwd);
	now = find_envp(envport, "PWD");
	if (now)
	{
		now->value = tmp3;
	}
	else
		free(tmp3);
	free(tmp4);
}

void	change_directory(char *path, t_envp **envport)
{
	char	**cmd_arr;
	t_envp	*now;

	now = find_envp(envport, "?");
	cmd_arr = ft_split(path, ' ');
	if (!chdir(cmd_arr[1]))
	{
		change_oldpwd(envport);
		change_pwd(envport);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd_arr[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(now->value);
		now->value = ft_strdup("1");
	}
	arr_free(cmd_arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolee <heolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:25:26 by heolee            #+#    #+#             */
/*   Updated: 2024/02/20 10:09:09 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arr_free(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**parsing_path(t_envp **envport)
{
	t_envp	*now;
	char	*path;
	char	**path_arr;

	now = *envport;
	while (now)
	{
		if (!ft_strcmp("PATH", now->name))
		{
			path = ft_strdup(now->value);
			path_arr = ft_split(path, ':');
			free(path);
			return (path_arr);
		}
		now = now->next;
	}
	return (NULL);
}

void	free_and_free(char *path_cmd, char **path_arr)
{
	free(path_cmd);
	arr_free(path_arr);
}

char	*check_now_dic(char *path)
{
	int			fd;

	if (!ft_strncmp("./", path, 2) || !ft_strncmp("/", path, 1))
	{
		fd = open(path, O_RDWR);
		if (errno == 13 || errno == 21)
		{
			if (errno == 13)
				syntax_error2(path, 1);
			else if (errno == 21)
				syntax_error2(path, 2);
			exit(126);
		}
		else if (errno == 2)
		{
			syntax_error2(path, 4);
			exit(127);
		}
		fd = access(path + 2, X_OK);
		if (fd != -1)
			return (path);
	}
	return (NULL);
}

char	*make_path(char **path_arr, char *cmd)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*ans_path;

	if (check_now_dic(cmd))
		return (cmd);
	path_cmd = ft_strjoin("/", cmd);
	i = -1;
	while (path_arr[++i])
	{
		ans_path = ft_strjoin(path_arr[i], path_cmd);
		fd = access(ans_path, X_OK);
		if (fd != -1)
		{
			free_and_free(path_cmd, path_arr);
			return (ans_path);
		}
		close(fd);
		free(ans_path);
	}
	free_and_free(path_cmd, path_arr);
	syntax_error2(cmd, 3);
	return (NULL);
}

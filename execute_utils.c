/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolee <heolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:29:07 by heolee            #+#    #+#             */
/*   Updated: 2024/02/20 10:09:04 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_access(char **cmd_arr, char **envp)
{
	int		fd1;
	int		fd2;

	fd1 = access(cmd_arr[0], X_OK);
	fd2 = open(cmd_arr[0], O_RDWR);
	if (fd1 != -1 && errno != 21)
	{
		if (execve(cmd_arr[0], cmd_arr, envp) == -1)
			exit(1);
	}
}

void	execve_cmd(t_node *node, t_envp **envport)
{
	char	**cmd_arr;
	char	*path;
	char	**path_arr;
	char	**envp;

	envp = make_envp(envport);
	path_arr = parsing_path(envport);
	cmd_arr = ft_split(node->data, ' ');
	check_access(cmd_arr, envp);
	if (!path_arr)
	{
		syntax_error2(cmd_arr[0], 4);
		exit(127);
	}
	if (!cmd_arr)
		exit(1);
	path = make_path(path_arr, cmd_arr[0]);
	if (!path)
		exit(127);
	if (execve(path, cmd_arr, envp) == -1)
		exit(1);
}

void	here_doc_read(int hd_fd, char *end_sign, t_envp **envport, int fd)
{
	char	*line;

	dup2(STDIN_FILENO, fd);
	signal(SIGINT, here_doc_handler);
	while (1)
	{
		line = readline("> ");
		if (signal_here_doc_handler(*envport))
		{
			dup2(fd, STDIN_FILENO);
			if (line)
				free(line);
			break ;
		}
		if (!line)
			break ;
		else if (!ft_memcmp(line, end_sign, ft_strlen(end_sign) + 1))
		{
			free(line);
			break ;
		}
		else
			here_doc_write(hd_fd, line, envport);
		free(line);
	}
}

void	chid_exit_code(int status, t_envp *now)
{
	int	i;

	i = 0;
	if (!ft_strcmp(now->value, "257"))
		i = 1;
	free(now->value);
	now->value = ft_itoa(WEXITSTATUS(status));
	if (WIFSIGNALED(status) == 1)
	{
		if (WTERMSIG(status) == 2 || WTERMSIG(status) == 3)
		{
			if (WTERMSIG(status) == 2)
				printf("\n");
			if (WTERMSIG(status) == 3)
				printf("Quit: 3\n");
			free(now->value);
			now->value = ft_itoa(WTERMSIG(status) + 128);
		}
	}
	if (i)
	{
		free(now->value);
		now->value = ft_strdup("1");
	}
}

void	wait_chid_process(int num, t_envp **envport, pid_t pid)
{
	int		status;
	int		i;
	t_envp	*now;

	now = find_envp(envport, "?");
	i = 0;
	while (i < num)
	{
		wait(&status);
		i++;
	}
	waitpid(pid, &status, 0);
	chid_exit_code(status, now);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolee <heolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:33:04 by heolee            #+#    #+#             */
/*   Updated: 2024/02/20 10:09:26 by dna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	red_read(t_node *node)
{
	int		infile_fd;

	access_error(node);
	infile_fd = open(node->data, O_RDONLY);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
}

void	red_write(t_node *node)
{
	int		outfile_fd;

	outfile_fd = open(node->data, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (outfile_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->data, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(1);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

void	red_here_doc(int hd_num)
{
	int		infile_fd;
	char	*num;
	char	*hd_name;

	num = ft_itoa(hd_num);
	hd_name = ft_strjoin("tmp", num);
	free(num);
	infile_fd = open(hd_name, O_RDONLY);
	if (infile_fd == -1)
		exit(1);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	free(hd_name);
}

void	red_append(t_node *node)
{
	int		outfile_fd;

	outfile_fd = open(node->data, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (outfile_fd == -1)
	{
		write(2, " Permission denied\n", 19);
		exit(1);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

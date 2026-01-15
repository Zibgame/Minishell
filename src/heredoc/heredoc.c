/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:09:32 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/15 11:17:10 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_heredoc(t_shell *shell, char *limiter, int write_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	free(line);
	free_shell(shell);
	close(write_fd);
	exit(0);
}

int	handle_heredoc(t_shell *shell, char *limiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	t_redir	*tmp;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		close(fd[0]);
		child_heredoc(shell, limiter, fd[1]);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	tmp = shell->cmd->redirs->next;
	
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}

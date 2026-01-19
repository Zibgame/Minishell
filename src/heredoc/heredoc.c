/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:09:32 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/19 13:41:13 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_loop(char *limiter, int write_fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
		line = NULL;
	}
	free(line);
}

static void	child_heredoc(t_shell *shell, char *limiter, int write_fd)
{
	signal(SIGINT, SIG_DFL);
	heredoc_loop(limiter, write_fd);
	close(write_fd);
	free_shell(shell);
	exit(0);
}

static int	handle_heredoc_error(int fd0, int fd1)
{
	if (fd0 != -1)
		close(fd0);
	if (fd1 != -1)
		close(fd1);
	return (-1);
}

int	handle_heredoc(t_shell *shell, char *limiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (handle_heredoc_error(fd[0], fd[1]));
	if (pid == 0)
	{
		close(fd[0]);
		child_heredoc(shell, limiter, fd[1]);
	}
	close(fd[1]);
	if (waitpid(pid, &status, 0) == -1 || WIFSIGNALED(status))
		return (handle_heredoc_error(fd[0], -1));
	return (fd[0]);
}
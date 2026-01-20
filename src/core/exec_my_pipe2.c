/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_my_pipe2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:59:48 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/20 11:26:46 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	fork_and_exec(t_shell *shell, t_pipedata *data, char *line)
{
	data->pid = fork();
	if (data->pid == -1)
		return (handle_fork_error(data), 0);
	if (data->pid == 0)
		exec_childda(shell, *data, line);
	data->last_pid = data->pid;
	parent_cleanup(data);
	data->cmd = get_next_cmd(data->cmd);
	return (1);
}

static int	prepare_pipe(t_pipedata *data)
{
	if (get_next_cmd(data->cmd))
	{
		if (pipe(data->pipefd) == -1)
			return (perror("pipe"), 0);
	}
	else
	{
		data->pipefd[0] = -1;
		data->pipefd[1] = STDOUT_FILENO;
	}
	return (1);
}

void	setup_child_fds(t_pipedata data)
{
	if (data.in_fd != -1 && data.in_fd != STDIN_FILENO)
	{
		dup2(data.in_fd, STDIN_FILENO);
		close(data.in_fd);
	}
	if (data.pipefd[1] != -1 && data.pipefd[1] != STDOUT_FILENO)
	{
		dup2(data.pipefd[1], STDOUT_FILENO);
		close(data.pipefd[1]);
	}
	if (data.pipefd[0] != -1 && data.pipefd[0] != STDIN_FILENO)
		close(data.pipefd[0]);
}

void	parent_cleanup(t_pipedata *data)
{
	if (data->in_fd != -1 && data->in_fd != STDIN_FILENO)
		close(data->in_fd);
	if (data->pipefd[1] != -1 && data->pipefd[1] != STDOUT_FILENO)
		close(data->pipefd[1]);
	data->in_fd = data->pipefd[0];
}

void	run_pipeline(t_shell *shell, t_pipedata *data, char *line)
{
	while (data->cmd)
	{
		if (!prepare_pipe(data))
			return ;
		if (!fork_and_exec(shell, data, line))
			return ;
	}
}

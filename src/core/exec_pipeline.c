/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:25:00 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/13 13:20:57 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static void	exec_child(t_shell *shell, t_pipedata data)
{
	char	*path;
	char	**argv;

	if (data.in_fd != STDIN_FILENO)
		dup2(data.in_fd, STDIN_FILENO);
	if (data.pipefd[1] != STDOUT_FILENO)
		dup2(data.pipefd[1], STDOUT_FILENO);
	if (data.cmd->type == BUILTINS)
		exit(exec_builtin_pipe(shell, data.cmd));
	path = get_cmd_path(shell, data.cmd->name);
	if (!path)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	argv = build_argv(data.cmd);
	if (!argv || apply_redirections(data.cmd))
	{
		shell->last_return = 1;
		exit(1);
	}
	else
		execve(path, argv, shell->envp_tmp);
	exit(1);
}

void	exec_pipeline(t_shell *shell)
{
	t_pipedata	data;

	data.cmd = shell->cmd;
	data.in_fd = STDIN_FILENO;
	data.last_pid = -1;
	while (data.cmd)
	{
		if (get_next_cmd(data.cmd))
			pipe(data.pipefd);
		else
			data.pipefd[1] = STDOUT_FILENO;
		data.pid = fork();
		if (data.pid == 0)
			exec_child(shell, data);
		if (data.pid > 0)
			data.last_pid = data.pid;
		if (data.in_fd != STDIN_FILENO)
			close(data.in_fd);
		if (data.pipefd[1] != STDOUT_FILENO)
			close(data.pipefd[1]);
		data.in_fd = data.pipefd[0];
		data.cmd = get_next_cmd(data.cmd);
	}
	waitpid(data.last_pid, &data.status, 0);
	shell->last_return = get_exit_status(data.status);
	while (wait(NULL) > 0)
		;
}

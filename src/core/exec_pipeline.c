/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:15:17 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/15 15:15:18 by zcadinot         ###   ########.fr       */
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

static void	free_child_exec(t_shell *shell, char *path, char **argv)
{
	if (path)
		free(path);
	if (argv)
		free_array(argv);
	free_shell(shell);
}

static void	close_child_fds(t_pipedata data)
{
	if (data.pipefd[0] != STDIN_FILENO)
		close(data.pipefd[0]);
	if (data.pipefd[1] != STDOUT_FILENO)
		close(data.pipefd[1]);
}

static void	exec_child(t_shell *shell, t_pipedata data, char *line)
{
	char	*path;
	char	**argv;

	if (data.in_fd != STDIN_FILENO)
		dup2(data.in_fd, STDIN_FILENO);
	if (data.pipefd[1] != STDOUT_FILENO)
		dup2(data.pipefd[1], STDOUT_FILENO);
	close_child_fds(data);
	free(line);
	
	if (apply_redirections(data. cmd))
	{
		free_shell(shell);
		exit(1);
	}
	
	if (data.cmd->type == BUILTINS)
		exit(exec_builtin_pipe(shell, data.cmd));
	path = get_cmd_path(shell, data.cmd->name);
	if (! path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		free_shell(shell);
		exit(127);
	}
	argv = build_argv(data.cmd);
	if (! argv)
	{
		free(path);
		free_shell(shell);
		exit(1);
	}
	execve(path, argv, shell->envp_tmp);
	free_child_exec(shell, path, argv);
	exit(126);
}

void	exec_pipeline(t_shell *shell, char *line)
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
			exec_child(shell, data, line);
		if (data.pid > 0)
			data.last_pid = data.pid;
		if (data.in_fd != STDIN_FILENO)
			close(data.in_fd);
		if (data.pipefd[1] != STDOUT_FILENO)
			close(data.pipefd[1]);
		data.in_fd = data.pipefd[0];
		data.cmd = get_next_cmd(data.cmd);
	}
	if (data.in_fd != STDIN_FILENO)
		close(data.in_fd);
	waitpid(data.last_pid, &data.status, 0);
	shell->last_return = get_exit_status(data.status);
	while (wait(NULL) > 0)
		;
}
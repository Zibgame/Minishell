/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:25:00 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/19 16:51:58 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	close_child_fds_or_get_status(t_pipedata data, int status, int i)
{
	if (i == 0)
	{
		if (data.pipefd[0] != STDIN_FILENO)
			close(data.pipefd[0]);
		if (data.pipefd[1] != STDOUT_FILENO)
			close(data.pipefd[1]);
		return (0);
	}
	else
	{
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
		return (1);
	}
}

static void	clean_exit(t_shell *shell, int err_code, char *path, char **argv)
{
	if (path)
		free(path);
	if (argv)
		free_array(argv);
	free_shell(shell);
	if (err_code == 127)
		ft_putstr_fd("minishell: command not found\n", 2);
	exit(err_code);
}

static void	exec_child(t_shell *shell, t_pipedata data, char *line)
{
	char	*path;
	char	**argv;

	if (data.in_fd != STDIN_FILENO)
		dup2(data.in_fd, STDIN_FILENO);
	if (data.pipefd[1] != STDOUT_FILENO)
		dup2(data.pipefd[1], STDOUT_FILENO);
	close_child_fds_or_get_status(data, 0, 0);
	free(line);
	if (apply_redirections(data.cmd))
		clean_exit(shell, 1, NULL, NULL);
	if (data.cmd->type == BUILTINS)
		exit(exec_builtin_pipe(shell, data.cmd));
	path = get_cmd_path(shell, data.cmd->name);
	if (!path)
		clean_exit(shell, 127, NULL, NULL);
	argv = build_argv(data.cmd);
	if (!argv)
		clean_exit(shell, 1, path, NULL);
	execve(path, argv, shell->envp_tmp);
	clean_exit(shell, 126, path, argv);
}

static void	chile(t_shell *shell, t_pipedata *data, char *line)
{
	while (data->cmd)
	{
		if (get_next_cmd(data->cmd))
			pipe(data->pipefd);
		else
			data->pipefd[1] = STDOUT_FILENO;
		data->pid = fork();
		if (data->pid == 0)
			exec_child(shell, *data, line);
		if (data->pid > 0)
			data->last_pid = data->pid;
		if (data->in_fd != STDIN_FILENO)
			close(data->in_fd);
		if (data->pipefd[1] != STDOUT_FILENO)
			close(data->pipefd[1]);
		data->in_fd = data->pipefd[0];
		data->cmd = get_next_cmd(data->cmd);
	}
}

void	exec_pipeline(t_shell *shell, char *line)
{
	t_pipedata	data;

	data.cmd = shell->cmd;
	data.in_fd = STDIN_FILENO;
	data.last_pid = -1;
	chile(shell, &data, line);
	ft_cmdclear(&shell->cmd);
	if (data.in_fd != STDIN_FILENO)
		close(data.in_fd);
	waitpid(data.last_pid, &data.status, 0);
	shell->last_return = close_child_fds_or_get_status(data, data.status, 1);
	while (wait(NULL) > 0)
		;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:25:00 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/20 10:44:06 by zcadinot         ###   ########.fr       */
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

static void	clean_exit(t_shell *shell, int err_code, char *path, char **argv)
{
	if (path)
		free(path);
	if (argv)
		free_array(argv);
	free_shell(shell);
	exit(err_code);
}

static void	exec_child(t_shell *shell, t_pipedata data, char *line)
{
	char	*path;
	char	**argv;

	if (data.in_fd != STDIN_FILENO)
	{
		dup2(data.in_fd, STDIN_FILENO);
		close(data.in_fd);
	}
	if (data.pipefd[1] != STDOUT_FILENO)
	{
		dup2(data.pipefd[1], STDOUT_FILENO);
		close(data.pipefd[1]);
	}
	if (data.pipefd[0] != -1 && data.pipefd[0] != STDIN_FILENO)
		close(data.pipefd[0]);
	free(line);
	if (apply_redirections(data.cmd))
		clean_exit(shell, 1, NULL, NULL);
	if (data.cmd->type == BUILTINS)
		exit(exec_builtin_pipe(shell, data.cmd));
	path = get_cmd_path(shell, data.cmd->name);
	if (!path)
	{
		ft_printf_fd("minishell: %s: command not found\n", 2, data.cmd->name);
		clean_exit(shell, 127, NULL, NULL);
	}
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
		{
			if (pipe(data->pipefd) == -1)
			{
				perror("pipe");
				return ;
			}
		}
		else
		{
			data->pipefd[0] = -1;
			data->pipefd[1] = STDOUT_FILENO;
		}
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
	shell->last_return = get_exit_status(data.status);
	while (wait(NULL) > 0)
		;
}

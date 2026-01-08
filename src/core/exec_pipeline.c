/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:25:00 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/08 23:05:18 by dadoune          ###   ########.fr       */
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

// static int	valid_redirs(t_shell *shell, t_cmd *cmd)
// {
// 	t_redir	*redirs;
	
// 	redirs = cmd->redirs;
// 	while (redirs)
// 	{
// 		if (handle_direct_path(shell, redirs->target))
// 			return (0);
// 		redirs = redirs->next;
// 	}
// 	return (1);
// }

static void	exec_child(t_shell *shell, t_cmd *cmd, int in_fd, int out_fd)
{
	char	*path;
	char	**argv;

	if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);
	if (cmd->type == BUILTINS)
		exit(exec_builtin_pipe(shell, cmd));
	path = get_cmd_path(shell, cmd->name);
	if (!path)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	argv = build_argv(cmd);
	if (!argv)
		exit(1);
	if (apply_redirections(cmd))
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
	t_cmd	*cmd;
	int		pipefd[2];
	int		in_fd;
	pid_t	pid;
	pid_t	last_pid;
	int		status;

	cmd = shell->cmd;
	in_fd = STDIN_FILENO;
	last_pid = -1;
	while (cmd)
	{
		// if (valid_redirs(shell, cmd))
		// {
			if (get_next_cmd(cmd))
				pipe(pipefd);
			else
				pipefd[1] = STDOUT_FILENO;
			pid = fork();
			if (pid == 0)
				exec_child(shell, cmd, in_fd, pipefd[1]);
			if (pid > 0)
				last_pid = pid;
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			if (pipefd[1] != STDOUT_FILENO)
				close(pipefd[1]);
			in_fd = pipefd[0];
		// }
		cmd = get_next_cmd(cmd);
	}
	waitpid(last_pid, &status, 0);
	shell->last_return = get_exit_status(status);
	while (wait(NULL) > 0)
		;
}


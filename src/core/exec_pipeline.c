/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:25:00 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/22 17:39:52 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_child(t_shell *shell, t_cmd *cmd, int in_fd, int out_fd)
{
	char	*path;
	char	**argv;

	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (cmd->type == BUILTINS)
		exit(exec_builtin_pipe(shell, cmd));
	path = get_cmd_path(shell, cmd->name);
	if (!path)
		exit(127);
	argv = build_argv(cmd);
	if (!argv)
		exit(1);
	execve(path, argv, shell->envp_tmp);
	exit(1);
}

void	exec_pipeline(t_shell *shell)
{
	t_cmd	*cmd;
	int		pipefd[2];
	int		in_fd;
	pid_t	pid;

	cmd = shell->cmd;
	in_fd = STDIN_FILENO;
	shell->in_pipeline = 1;
	while (cmd)
	{
		if (get_next_cmd(cmd))
			pipe(pipefd);
		else
			pipefd[1] = STDOUT_FILENO;
		pid = fork();
		if (pid == 0)
			exec_child(shell, cmd, in_fd, pipefd[1]);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (pipefd[1] != STDOUT_FILENO)
			close(pipefd[1]);
		in_fd = pipefd[0];
		cmd = get_next_cmd(cmd);
	}
	while (wait(NULL) > 0)
		;
	shell->in_pipeline = 0;
}

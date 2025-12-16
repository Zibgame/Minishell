/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:25:00 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/16 11:51:22 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_child(t_shell *shell, t_cmd *cmd, int in_fd, int out_fd)
{
	char	*path;
	char	**argv;

	if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);

	if (cmd->type == BUILTINS)
	{
		exec_builtins(shell);
		exit(shell->last_return);
	}
	path = get_cmd_path(shell, cmd->name);
	if (!path)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	argv = build_argv(cmd);
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
	while (cmd)
	{
		if (cmd->next && cmd->next->type == PIPE)
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
		if (cmd->next && cmd->next->type == PIPE)
			cmd = cmd->next->next;
		else
			break ;
	}
	while (wait(NULL) > 0)
		;
}

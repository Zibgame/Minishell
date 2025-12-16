/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:25:00 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/16 11:31:34 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		{
			if (pipe(pipefd) == -1)
				return ;
		}
		else
		{
			pipefd[0] = STDIN_FILENO;
			pipefd[1] = STDOUT_FILENO;
		}
		pid = fork();
		if (pid == 0)
			//exec le child
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

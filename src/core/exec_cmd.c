/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:04:17 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/11 13:24:05 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_shell *shell)
{
	pid_t	pid;
	char	**args;
	char	*path;

	if (!shell->cmd)
		return ;
	path = get_cmd_path(shell, shell->cmd->name);
	if (!path)
	{
		printf("minishell: %s: command not found\n", shell->cmd->name);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		args = 
		execve(path, args, shell->envp_tmp);
		perror("execve");
		free_array(args);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	free_array(args);
	shell->last_return = WEXITSTATUS(pid);
	free(path);
}

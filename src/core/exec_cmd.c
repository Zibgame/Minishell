/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:04:17 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 15:59:13 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_shell *shell, char *line)
{
	pid_t	pid;
	char	**args;
	char	*path;

	args = ft_split(line, ' ');
	if (!args)
		return ;
	path = get_cmd_path(shell, args[0]);
	if (!path)
	{
		printf("minishell: %s: command not found\n", args[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, args, shell->envp_tmp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	free(path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:04:17 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/02 09:27:36 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_shell shell, char *line)
{
	pid_t	pid;
	char	**args;

	args = ft_split(line, ' ');
	if (!args)
		return ;
	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, shell.env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:04:17 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 09:44:25 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_shell shell, char *line)
{
	pid_t	pid;
	char	**args;
	char	*bin;

	args = ft_split(line, ' ');
	free(line);
	if (!args)
		return ;
	bin = get_cmd(args[0], shell.env);
	if (!bin)
	{
		printf("command not found: %s\n", args[0]);
		free(line);
		free(args);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(bin, args, shell.env);
		perror("execve");
		free(args);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	free(args);
	return ;
}

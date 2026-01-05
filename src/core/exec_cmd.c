/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:04:17 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/05 14:24:25 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_IN)
			fd = open(r->target, O_RDONLY);
		else if (r->type == R_OUT)
			fd = open(r->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (r->type == R_APPEND)
			fd = open(r->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = r->fd;
		if (fd < 0)
			return (perror(r->target), 1);
		if (r->type == R_IN || r->type == R_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		r = r->next;
	}
	return (0);
}

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
		apply_redirections(shell->cmd);
		execve(path, args, shell->envp_tmp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	shell->last_return = WEXITSTATUS(pid);
	free(path);
}

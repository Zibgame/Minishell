/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:04:17 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/19 16:53:53 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	return_type(t_shell *shell, char *line)
{
	if (!ft_strncmp("$", line, 1) && ft_strncmp("$?", line, 2)
		&& ft_strlen(line) > 1)
		shell->last_return = 0;
	else
		shell->last_return = 127;
}

int	handle_direct_path(t_shell *shell, char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) != 0)
	{
		ft_printf_fd("minishell: %s: No such file or directory\n", 2, cmd);
		shell->last_return = 127;
		return (1);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_printf_fd("minishell: %s: Is a directory\n", 2, cmd);
		shell->last_return = 126;
		return (1);
	}
	if (access(cmd, X_OK) != 0 || access(cmd, R_OK) != 0)
	{
		ft_printf_fd("minishell: %s: Permission denied\n", 2, cmd);
		shell->last_return = 126;
		return (1);
	}
	return (0);
}

static char	**prepare_args(char *line)
{
	char	**args;

	args = ft_split(line, ' ');
	if (!args)
		return (NULL);
	args = clean_empty_args(args);
	if (!args || !args[0])
	{
		free_array(args);
		return (NULL);
	}
	return (args);
}

static char	*resolve_path(t_shell *shell, char **args)
{
	char	*path;

	if (ft_strchr(args[0], '/'))
	{
		if (handle_direct_path(shell, args[0]))
			return (NULL);
		return (ft_strdup(args[0]));
	}
	path = get_cmd_path(shell, args[0]);
	if (!path)
	{
		ft_printf_fd("minishell: %s: command not found\n", 2, args[0]);
		return_type(shell, args[0]);
	}
	return (path);
}

static void	exec_child(t_shell *shell, char *path, char **args)
{
	signal_child();
	if (apply_redirections(shell->cmd))
		exit(1);
	execve(path, args, shell->envp_tmp);
	perror("execve");
	exit(126);
}

static void	handle_parent(t_shell *shell, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_return = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_return = 128 + WTERMSIG(status);
}

void	exec_cmd(t_shell *shell, char *line)
{
	pid_t	pid;
	char	**args;
	char	*path;

	args = prepare_args(line);
	if (!args)
		return ;
	path = resolve_path(shell, args);
	if (!path)
	{
		free_array(args);
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_child(shell, path, args);
	handle_parent(shell, pid);
	free(path);
	free_array(args);
}
